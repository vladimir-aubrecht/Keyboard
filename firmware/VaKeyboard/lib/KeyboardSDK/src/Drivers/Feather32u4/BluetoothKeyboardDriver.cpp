#ifdef FEATHER32U4

#include "BluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(
	Adafruit_BluefruitLE_SPI *ble,
	IBatteryDriver *batteryDriver,
	IKeyboardDescriptor *keyboardDescriptor,
	ILogger *logger)
{
	this->keyboardDescriptor = keyboardDescriptor;
	this->ble = ble;
	//this->logger = logger;
	this->batteryDriver = batteryDriver;
	Init();
}

void BluetoothKeyboardDriver::ResetPairing()
{
	if (!this->ble->factoryReset())
	{
		// this->logger->logError(F("Couldn't factory reset"));
		return;
	}

	Init();
}

void BluetoothKeyboardDriver::Init()
{
	if (!this->ble->begin(true))
	{
		// this->logger->logError(F("Couldn't find Bluefruit, make sure it's in Command mode & check wiring?"));
		return;
	}

	this->ble->echo(false);

	// Some of these methods should have checks and logging, but it's dropped to save flash size as it "should never happen" anyway (lets see when it will be reported :P).
	this->ble->sendCommandCheckOK(F("AT+GAPDEVNAME=VaKeyboard"));
	this->ble->sendCommandCheckOK(F("AT+BleHIDEn=On"));

	this->ble->sendCommandCheckOK(F("AT+BLEBATTEN=on"));
	this->ble->sendCommandCheckOK("AT+BLEBATTVAL=" + batteryDriver->readBatteryLevel());

	this->ble->reset();
}

bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	if (this->ble->isConnected())
	{
		this->currentStateMatrix = this->UpdateStateMatrix(this->currentStateMatrix, pressedKeysMatrix, releasedKeysMatrix);

		uint8_t *buffer = new uint8_t[currentStateMatrix->numberOfRows * currentStateMatrix->numberOfColumns];

		uint8_t layout = this->keyboardDescriptor->getSelectedLayer(currentStateMatrix);

		auto keymap = this->keyboardDescriptor->getKeyMap()[layout];
		uint8_t keyCount = ScanForPressedRegularKeys(currentStateMatrix, keymap, buffer);
		uint8_t modificators = ScanForModificators(currentStateMatrix);

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
		// this->logger->logWarning(F("Keyboard not connected :("));
		return false;
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
			uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
			uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

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

uint8_t BluetoothKeyboardDriver::ScanForPressedRegularKeys(Matrix *matrix, KeyCode **keymap, uint8_t *foundKeys)
{
	uint8_t foundKeyCount = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			auto currentKey = keymap[row][column];

			uint8_t isPressed = matrix->getBit(row, column);

			if (isPressed && currentKey < 0xE0) // without modificator keys, 0xE0 starts modificator key
			{
				foundKeys[foundKeyCount] = currentKey;
				foundKeyCount++;
			}
		}
	}

	return foundKeyCount;
}

uint8_t BluetoothKeyboardDriver::ScanForModificators(Matrix *matrix)
{
	uint8_t modificators = 0;

	auto coordMap = this->keyboardDescriptor->getCoordinatesMap();

	for (uint8_t i = 0xE0; i < 0xff; i++)
	{
		uint8_t isScannedPress = matrix->getBit(coordMap[i - 0x76]->getRow(), coordMap[i - 0x76]->getColumn());

	 	if (isScannedPress)
	 	{
	 		modificators |= (1 << (i - 0xE0));
	 	}

	}

	return modificators;
}

bool BluetoothKeyboardDriver::SendKeypresses(uint8_t modificators, uint8_t *keys)
{
	char* cmd = this->GenerateCommandBytes(modificators, keys);
	ble->print(AT_KEYBOARD_CODE);
	ble->println(cmd);

	return !ble->waitForOK();
}

bool BluetoothKeyboardDriver::SendRelease()
{
	ble->print(AT_KEYBOARD_CODE);
	ble->println("00-00");

	return !ble->waitForOK();
}

char* BluetoothKeyboardDriver::GenerateCommandBytes(uint8_t modifier, uint8_t* keys)
{
	char hex[] = "0123456789ABCDEF";
	char* cmd = "00-00-00-00-00-00-00-00";

	cmd[0] = hex[modifier / 16];
	cmd[1] = hex[modifier % 16];

	for (uint8_t i = 0; i < this->maxKeyCountInReport; i++)
	{
		cmd[6 + 2*i + i] = hex[keys[i] / 16];
		cmd[7 + 2*i + i] = hex[keys[i] % 16];
	}

	return cmd;
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

#endif