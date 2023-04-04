#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;
	USB.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	USBHIDKeyboard keyboard;
	keyboard.begin();
	auto keymap = this->keyboardDescriptor->getKeyMap()[0];

	bool isPress = false;
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			auto currentKey = keymap[row][column];

			uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
			uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

			if (isPressed)
			{
				isPress = true;

				keyboard.pressRaw(currentKey);
			}
			else if (isReleased)
			{
				keyboard.releaseRaw(currentKey);
			}
		}
	}
	keyboard.end();
	return isPress;
}

void UsbHidKeyboardDriver::ResetPairing()
{
}

void UsbHidKeyboardDriver::ResetState()
{
	USBHIDKeyboard keyboard;
	keyboard.begin();
	keyboard.releaseAll();
	keyboard.end();
}

#endif