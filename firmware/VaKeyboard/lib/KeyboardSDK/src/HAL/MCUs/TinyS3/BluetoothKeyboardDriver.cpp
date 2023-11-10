#ifdef TINYS3

#include "BluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(
	BleKeyboard* bleKeyboard,
	IBatteryDriver *batteryDriver,
	BaseKeyboardDescriptor *keyboardDescriptor,
	ILogger *logger)
{
	this->bleKeyboard = bleKeyboard;
	this->keyboardDescriptor = keyboardDescriptor;
	this->logger = logger;
	this->batteryDriver = batteryDriver;
}

void BluetoothKeyboardDriver::ResetPairing()
{
}

bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	if (this->bleKeyboard->isConnected())
	{
		this->currentStateMatrix = this->UpdateStateMatrix(this->currentStateMatrix, pressedKeysMatrix, releasedKeysMatrix);

		uint8_t *buffer = new uint8_t[currentStateMatrix->numberOfRows * currentStateMatrix->numberOfColumns];

		uint8_t layout = this->keyboardDescriptor->getSelectedLayer(currentStateMatrix);

		auto keymap = this->keyboardDescriptor->getKeyMap()[layout];
		uint8_t modificators = 0;
		uint8_t keyCount = ScanForPressedKeys(currentStateMatrix, keymap, buffer, &modificators);

		if (keyCount == 0)
		{
			this->bleKeyboard->releaseAll();
			return false;
		}

		uint8_t keysToSendArraySize = keyCount / this->maxKeyCountInReport;

		if (keyCount % this->maxKeyCountInReport > 0)
			keysToSendArraySize++;

		uint8_t **keysToSend = new uint8_t *[keysToSendArraySize];
		SplitToArrayOf(buffer, keyCount, keysToSend, this->maxKeyCountInReport);

		BleKeyReport keyReport;
		for (uint8_t i = 0; i < keysToSendArraySize && keyCount > 0; i++)
		{
			keyReport.modifiers = modificators;
		 	for (uint8_t k = 0; k < this->maxKeyCountInReport; k++)
		 	{
		 		keyReport.keys[k] = keysToSend[i][k];
		 	}

		 	this->bleKeyboard->sendReport(&keyReport);
			delete keysToSend[i];
		}

		delete buffer;
		delete keysToSend;

		return true;
	}
	else
	{
		this->logger->logWarning(F("Keyboard not connected :("));
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

uint8_t BluetoothKeyboardDriver::ScanForPressedKeys(Matrix *matrix, KeyCode **keymapProvider, uint8_t *foundKeys, uint8_t *modificators)
{
	uint8_t foundKeyCount = 0;
	(*modificators) = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			auto currentKey = keymapProvider[row][column];

			uint8_t isPressed = matrix->getBit(row, column);

			if (isPressed)
			{
				if (currentKey < 0xE0) // without modificator keys, 0xE0 starts modificator key
				{
					foundKeys[foundKeyCount] = currentKey;
					foundKeyCount++;
				}
				else if (currentKey >= 0xE0) // modificator keys
				{
					uint8_t bit = (1 << (currentKey - 0xE0));
					(*modificators) |= bit;
				}
			}
		}
	}

	return foundKeyCount;
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
		BleKeyboard* bleKeyboard = new BleKeyboard("XBoard", "VASoft", batteryDriver->readBatteryLevel());
		bleKeyboard->begin();
		BluetoothKeyboardDriver::instance = new BluetoothKeyboardDriver(bleKeyboard, batteryDriver, keyboardDescriptor, logger);	
	}

    return BluetoothKeyboardDriver::instance;
}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::GetInstance()
{
	return BluetoothKeyboardDriver::instance;
}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::instance = NULL;

#endif