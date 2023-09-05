#ifdef TINYS3

#include "BluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(
	IBatteryDriver *batteryDriver,
	BaseKeyboardDescriptor *keyboardDescriptor,
	ILogger *logger)
{
	this->keyboardDescriptor = keyboardDescriptor;
	//this->logger = logger;
	this->batteryDriver = batteryDriver;
	Init();
}

void BluetoothKeyboardDriver::ResetPairing()
{
	Init();
}

void BluetoothKeyboardDriver::Init()
{
	this->bleKeyboard = new BleKeyboard("XBoard", "VASoft", this->batteryDriver->readBatteryLevel());
	this->bleKeyboard->begin();
}

bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	if (this->bleKeyboard->isConnected())
	{
		this->currentStateMatrix = this->UpdateStateMatrix(this->currentStateMatrix, pressedKeysMatrix, releasedKeysMatrix);

		uint8_t *buffer = new uint8_t[currentStateMatrix->numberOfRows * currentStateMatrix->numberOfColumns];

		uint8_t layout = this->keyboardDescriptor->getSelectedLayer(currentStateMatrix);

		auto keymap = this->keyboardDescriptor->getKeyMap()[layout];
		uint8_t keyCount = ScanForPressedRegularKeys(currentStateMatrix, keymap, buffer);
		uint8_t modificators = ScanForModificators(currentStateMatrix, keymap);

		for (uint8_t i = 0; i < keyCount; i++)
		{
			this->bleKeyboard->press(buffer[i]);
		}

		if (keyCount == 0 && modificators != 0)
		{
			//TODO: send modificators here
			//this->bleKeyboard->press(buffer[i]);
		}

		delete buffer;

		if (keyCount == 0)
		{
			this->bleKeyboard->releaseAll();
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

uint8_t BluetoothKeyboardDriver::ScanForPressedRegularKeys(Matrix *matrix, KeyCode **keymapProvider, uint8_t *foundKeys)
{
	uint8_t foundKeyCount = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			auto currentKey = keymapProvider[row][column];

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

uint8_t BluetoothKeyboardDriver::ScanForModificators(Matrix *matrix, KeyCode **keymapProvider)
{
	uint8_t modificators = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			auto currentKey = keymapProvider[row][column];

			uint8_t isScannedPress = matrix->getBit(row, column);

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

String BluetoothKeyboardDriver::ConvertToHexCode(uint8_t code)
{
	String hexCode = String(code, HEX);

	if (code < 0x10)
	{
		hexCode = "0" + hexCode;
	}

	return hexCode;
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
	this->bleKeyboard->releaseAll();
}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger)
{
	if (BluetoothKeyboardDriver::instance == NULL)
	{
		BluetoothKeyboardDriver::instance = new BluetoothKeyboardDriver(batteryDriver, keyboardDescriptor, logger);	
	}

    return BluetoothKeyboardDriver::instance;
}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::GetInstance()
{
	return BluetoothKeyboardDriver::instance;
}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::instance = NULL;

#endif