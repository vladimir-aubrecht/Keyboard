#ifdef FEATHER32U4

#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;
	NKROKeyboard.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	auto coordMap = this->keyboardDescriptor->getCoordinatesMap();
	isKeyMenuHold |= pressedKeysMatrix->getBit(coordMap[HID_KEYBOARD_MENU - 0x76]->getRow(), coordMap[HID_KEYBOARD_MENU - 0x76]->getColumn());
	isKeyMenuHold &= ~(releasedKeysMatrix->getBit(coordMap[HID_KEYBOARD_MENU - 0x76]->getRow(), coordMap[HID_KEYBOARD_MENU - 0x76]->getColumn()));
	uint8_t layout = isKeyMenuHold ? 1 : 0;

	bool isPress = false;
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			auto keymap = this->keyboardDescriptor->getKeyMap()[layout];
			KeyboardKeycode currentKey = keymap[row][column];

			uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
			uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

			if (isPressed)
			{
				isPress = true;

				//NKROKeyboard doesn't support multimedia keys :-/ 
				if (currentKey >= HID_KEYBOARD_MUTE && currentKey <= HID_KEYBOARD_VOLUME_DOWN)
				{
					Keyboard.press(currentKey);
				}
				else
				{
					NKROKeyboard.press(currentKey);
				}
			}
			else if (isReleased)
			{
				if (currentKey >= HID_KEYBOARD_MUTE && currentKey <= HID_KEYBOARD_VOLUME_DOWN)
				{
					Keyboard.release(currentKey);
				}
				else
				{
					NKROKeyboard.release(currentKey);
				}
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