#include "BluetoothKeyboardDriver.h"
#include "../Matrix/Convertors.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(Adafruit_BluefruitLE_SPI *ble)
{
	this->ble = ble;

	if (!this->ble->begin(true))
	{
		Serial.println("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
	}

	if (!ble->factoryReset())
	{
		Serial.println(F("Couldn't factory reset"));
	}

	ble->echo(false);

	if (!ble->sendCommandCheckOK(F("AT+GAPDEVNAME=VaKeyboard")))
	{
		Serial.println("Could not set device name?");
	}

	if (!ble->sendCommandCheckOK(F("AT+BleHIDEn=On")))
	{
		Serial.println("Could not enable Keyboard");
	}

	if (!ble->reset())
	{
		Serial.println("Couldn't reset??");
	}
}

void BluetoothKeyboardDriver::SendKeys(Matrix *scannedKeysMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider)
{
	if (this->ble->isConnected())
	{
		this->currentStateMatrix = this->UpdateStateMatrix(this->currentStateMatrix, pressedKeysMatrix, releasedKeysMatrix);

		uint8_t *buffer = new uint8_t[currentStateMatrix->numberOfRows * currentStateMatrix->numberOfColumns];

		uint8_t keyCount = ScanForPressedRegularKeys(currentStateMatrix, keymapProvider, buffer);
		uint8_t modificators = ScanForModificators(scannedKeysMatrix, keymapProvider);

		uint8_t keysToSendArraySize = keyCount / 5;

		if (keyCount % 5 > 0)
			keysToSendArraySize++;

		uint8_t **keysToSend = new uint8_t *[keysToSendArraySize];
		SplitToArrayOf5(buffer, keyCount, keysToSend);

		for (uint8_t i = 0; i < keysToSendArraySize && keyCount > 0; i++)
		{
			this->SendKeypresses(modificators, keysToSend[i]);
			delete keysToSend[i];
		}

		if (keyCount == 0 && modificators != 0)
		{
			uint8_t keys[5]{0, 0, 0, 0, 0};
			this->SendKeypresses(modificators, keys);
		}

		delete buffer;
		delete keysToSend;

		if (keyCount == 0)
		{
			this->SendRelease();
		}
	}
	else
	{
		Serial.println("Keyboard not connected :(");
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
	String cmd = this->ConvertToHexCode(modificators) + "-00";

	for (int i = 0; i < 5; i++)
	{
		cmd += "-" + this->ConvertToHexCode(keys[i]);
	}

	// Serial.println(cmd);
	ble->println("AT+BLEKEYBOARDCODE=" + cmd);

	return !ble->waitForOK();
}

bool BluetoothKeyboardDriver::SendRelease()
{
	ble->println("AT+BLEKEYBOARDCODE=00-00");

	return !ble->waitForOK();
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

void BluetoothKeyboardDriver::SplitToArrayOf5(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray)
{
	uint8_t outputArraySize = arrayLength / 5;

	if (arrayLength % 5 > 0)
		outputArraySize++;

	for (uint8_t i = 0; i < outputArraySize; i++)
	{
		outputArray[i] = new uint8_t[5];

		for (uint8_t j = 0; j < 5; j++)
		{
			if (i * 5 + j < arrayLength)
			{
				outputArray[i][j] = array[i * 5 + j];
			}
			else
			{
				outputArray[i][j] = 0;
			}
		}
	}
}