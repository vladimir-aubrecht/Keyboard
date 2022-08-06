#ifdef ARDUINO_MICRO

#include "UsbHidKeyboardDriver.h"
#include "HID-Project.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;
	Consumer.begin();
	NKROKeyboard.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	bool isPress = false;

	auto coordMap = this->keyboardDescriptor->getCoordinatesMap();
	isKeyMenuHold |= pressedKeysMatrix->getBit(coordMap[HID_KEYBOARD_MENU - 0x76]->getRow(), coordMap[HID_KEYBOARD_MENU - 0x76]->getColumn());
	isKeyMenuHold &= ~(releasedKeysMatrix->getBit(coordMap[HID_KEYBOARD_MENU - 0x76]->getRow(), coordMap[HID_KEYBOARD_MENU - 0x76]->getColumn()));

	if (isKeyMenuHold && this->keyboardDescriptor->getLayersCount() > 1) {
		for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
		{
			for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
			{
				auto keymap = this->keyboardDescriptor->getKeyMap()[1];
				auto currentKey = keymap[row][column];

				auto keyType = this->keyboardDescriptor->getKeyType(1, row, column);

				if (keyType != KeyType::MEDIA)
				{
					continue;
				}

				uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
				uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

				if (isPressed)
				{
					isPress = true;
					Consumer.press((ConsumerKeycode)currentKey);
				}
				else if (isReleased)
				{
					Consumer.release((ConsumerKeycode)currentKey);
				}
			}
		}
	}
	else
	{
		for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
		{
			for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
			{
				auto keymap = this->keyboardDescriptor->getKeyMap()[0];
				auto currentKey = keymap[row][column];

				uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
				uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

				if (isPressed)
				{
					NKROKeyboard.press((KeyboardKeycode)currentKey);
					isPress = true;
				}
				else if (isReleased)
				{
					NKROKeyboard.release((KeyboardKeycode)currentKey);
				}
			}
		}

		NKROKeyboard.send();
	}
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