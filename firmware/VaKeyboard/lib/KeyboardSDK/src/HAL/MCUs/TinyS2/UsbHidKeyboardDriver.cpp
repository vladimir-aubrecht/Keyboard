#ifdef TINYS2

#include "UsbHidKeyboardDriver.h"

USBHIDKeyboard keyboard;

UsbHidKeyboardDriver::UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;

	keyboard.begin();	
	USB.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
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
				keyboard.pressRaw((uint8_t)currentKey);
			}
			else if (isReleased)
			{
				keyboard.releaseRaw((uint8_t)currentKey);
			}
		}
	}

	return isPress;
}

void UsbHidKeyboardDriver::ResetPairing()
{
}

void UsbHidKeyboardDriver::ResetState()
{
	keyboard.releaseAll();
}

#endif