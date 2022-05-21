#include "BluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(Adafruit_BluefruitLE_SPI *ble, ILogger *logger)
{
	this->ble = ble;
	this->logger = logger ?: new NullLogger();
	Init();
}

void BluetoothKeyboardDriver::ResetPairing()
{
	if (!this->ble->factoryReset())
	{
		this->logger->logError(F("Couldn't factory reset"));
		return;
	}

	Init();
}

void BluetoothKeyboardDriver::Init()
{
	if (!this->ble->begin(true))
	{
		this->logger->logError(F("Couldn't find Bluefruit, make sure it's in Command mode & check wiring?"));
		return;
	}

	this->ble->echo(false);

	if (!this->ble->sendCommandCheckOK(F("AT+GAPDEVNAME=VaKeyboard")))
	{
		this->logger->logError(F("Could not set device name?"));
		return;
	}

	if (!this->ble->sendCommandCheckOK(F("AT+BleHIDEn=On")))
	{
		this->logger->logError(F("Could not enable Keyboard"));
		return;
	}

	if (!this->ble->reset())
	{
		this->logger->logWarning(F("Couldn't reset??"));
	}
}

bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider)
{
	if (this->ble->isConnected())
	{
		this->currentStateMatrix = this->UpdateStateMatrix(this->currentStateMatrix, pressedKeysMatrix, releasedKeysMatrix);

		uint8_t *buffer = new uint8_t[currentStateMatrix->numberOfRows * currentStateMatrix->numberOfColumns];

		uint8_t keyCount = ScanForPressedRegularKeys(currentStateMatrix, keymapProvider, buffer);
		uint8_t modificators = ScanForModificators(currentStateMatrix, keymapProvider);

		uint8_t keysToSendArraySize = keyCount / this->maxKeyCountInReport;

		if (keyCount % this->maxKeyCountInReport > 0)
			keysToSendArraySize++;

		uint8_t **keysToSend = new uint8_t *[keysToSendArraySize];
		SplitToArrayOf(buffer, keyCount, keysToSend, this->maxKeyCountInReport);

		for (uint8_t i = 0; i < keysToSendArraySize && keyCount > 0; i++)
		{
			this->SendKeypresses(modificators, keysToSend[i]);
			delete keysToSend[i];
		}

		if (keyCount == 0 && modificators != 0)
		{
			uint8_t keys[this->maxKeyCountInReport]{0, 0, 0, 0, 0};
			this->SendKeypresses(modificators, keys);
		}

		delete buffer;
		delete keysToSend;

		if (keyCount == 0)
		{
			this->SendRelease();
			return false;
		}

		return true;
	}
	else
	{
		this->logger->logWarning(F("Keyboard not connected :("));
	}
}

Matrix *BluetoothKeyboardDriver::UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	if (stateMatrix == NULL)
	{
		stateMatrix = new Matrix(pressedKeysMatrix->numberOfRows, pressedKeysMatrix->numberOfColumns);
	}

	for (uint8_t row = 0; row < stateMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < stateMatrix->numberOfColumns; column++)
		{
			bool isPressed = (pressedKeysMatrix->matrixData[row] >> column) & 1 == 1;
			bool isReleased = ((releasedKeysMatrix->matrixData[row] >> column) & 1) == 1;

			if (isPressed)
			{
				stateMatrix->matrixData[row] |= (((uint32_t)1) << column);
			}
			else if (isReleased)
			{
				stateMatrix->matrixData[row] &= ~(((uint32_t)1) << column);
			}
		}
	}

	return stateMatrix;
}

uint8_t BluetoothKeyboardDriver::ScanForPressedRegularKeys(Matrix *matrix, KeyboardKeycode **keymapProvider, uint8_t *foundKeys)
{
	uint8_t foundKeyCount = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			KeyboardKeycode currentKey = keymapProvider[row][column];

			bool isPressed = (matrix->matrixData[row] >> column) & 1 == 1;

			if (isPressed && currentKey < 0xE0) // without modificator keys, 0xE0 starts modificator key
			{
				foundKeys[foundKeyCount] = currentKey;
				foundKeyCount++;
			}
		}
	}

	return foundKeyCount;
}

uint8_t BluetoothKeyboardDriver::ScanForModificators(Matrix *matrix, KeyboardKeycode **keymapProvider)
{
	uint8_t modificators = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			KeyboardKeycode currentKey = keymapProvider[row][column];

			bool isScannedPress = (matrix->matrixData[row] >> column) & 1 == 1;

			if (isScannedPress)
			{
				if (currentKey >= 0xE0) // modificator keys
				{
					uint8_t bit = (1 << (currentKey - 0xE0));
					modificators |= bit;
				}
			}
		}
	}

	return modificators;
}

bool BluetoothKeyboardDriver::SendKeypresses(uint8_t modificators, uint8_t *keys)
{
	char cmd[20];
	strcpy(cmd, this->ConvertToHexCode(modificators));
	strcat(cmd, "-00");

	for (int i = 0; i < this->maxKeyCountInReport; i++)
	{
		strcat(cmd, "-");
		strcat(cmd, this->ConvertToHexCode(keys[i]));
	}

	ble->print("AT+BLEKEYBOARDCODE=");
	ble->println(cmd);

	return !ble->waitForOK();
}

bool BluetoothKeyboardDriver::SendRelease()
{
	ble->println(F("AT+BLEKEYBOARDCODE=00-00"));

	return !ble->waitForOK();
}

const char *BluetoothKeyboardDriver::ConvertToHexCode(uint8_t code)
{
	String hexCode = String(code, HEX);

	if (code < 0x10)
	{
		hexCode = "0" + hexCode;
	}

	return hexCode.c_str();
}

void BluetoothKeyboardDriver::SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength)
{
	uint8_t outputArraySize = arrayLength / innerArrayLength;

	if (arrayLength % innerArrayLength > 0)
		outputArraySize++;

	for (uint8_t i = 0; i < outputArraySize; i++)
	{
		outputArray[i] = new uint8_t[innerArrayLength];

		for (uint8_t j = 0; j < innerArrayLength; j++)
		{
			if (i * innerArrayLength + j < arrayLength)
			{
				outputArray[i][j] = array[i * innerArrayLength + j];
			}
			else
			{
				outputArray[i][j] = 0;
			}
		}
	}
}

void BluetoothKeyboardDriver::ResetState()
{
	this->currentStateMatrix = NULL;
	this->SendRelease();
}