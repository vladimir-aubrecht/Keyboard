#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "BluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(
	IBatteryDriver *batteryDriver,
	IKeyboardDescriptor *keyboardDescriptor,
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
	
}

bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	return false;
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

bool BluetoothKeyboardDriver::SendKeypresses(uint8_t modificators, uint8_t *keys)
{
	String cmd = this->ConvertToHexCode(modificators) + "-00";

	for (int i = 0; i < this->maxKeyCountInReport; i++)
	{
		cmd += "-" + this->ConvertToHexCode(keys[i]);
	}

	return false;
}

bool BluetoothKeyboardDriver::SendRelease()
{
	return false;
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
	this->SendRelease();
}

#endif