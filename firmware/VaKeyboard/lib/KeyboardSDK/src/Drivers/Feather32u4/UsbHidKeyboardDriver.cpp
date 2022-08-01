#ifdef FEATHER32U4

#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;
	NKROKeyboard.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	bool isPress = false;
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			auto keymap = this->keyboardDescriptor->getKeyMap()[0];
			KeyboardKeycode currentKey = keymap[row][column];

			uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
			uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

			if (isPressed)
			{
				isPress = true;
				
				NKROKeyboard.press(currentKey);
			}
			else if (isReleased)
			{
				NKROKeyboard.release(currentKey);
			}
		}
	}

	NKROKeyboard.send();

	return isPress;
}

void UsbHidKeyboardDriver::ResetPairing()
{
}

void UsbHidKeyboardDriver::ResetState()
{
	NKROKeyboard.releaseAll();
}

#endif