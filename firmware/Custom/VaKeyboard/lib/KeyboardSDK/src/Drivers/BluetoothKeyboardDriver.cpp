#ifdef ESP32

#include "BluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver()
{
	this->bleKeyboard = new BleKeyboard("VA Keyboard", "VASoft", 100U);
	this->bleKeyboard->begin();
}

void BluetoothKeyboardDriver::SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, uint16_t** keymapProvider)
{
	if (this->bleKeyboard->isConnected())
	{
		for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
		{
			for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
			{
				uint16_t currentKey = keymapProvider[row][column];

				bool isPressed = (pressedKeysMatrix->matrixData[row] >> column) & 1 == 1;
				bool isReleased = (releasedKeysMatrix->matrixData[row] >> column) & 1 == 1;

				if (isPressed)
				{
					this->bleKeyboard->press(currentKey);
				}
				else if (isReleased)
				{
					this->bleKeyboard->release(currentKey);
				}
			}
		}
	}
	else
	{
		Serial.println("Keyboard not connected :(");
	}
}

#else
#pragma message "Detected not ESP32, skipping compilation of BluetoothKeyboardDriver as don't know if device has bluetooth."
#endif