#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor, USBHIDKeyboard* usbHidKeyboard)
{
	this->keyboardDescriptor = keyboardDescriptor;

	this->usbHidKeyboard = usbHidKeyboard;

	this->usbHidKeyboard->begin();
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
				
				this->usbHidKeyboard->press(currentKey);
			}
			else if (isReleased)
			{
				this->usbHidKeyboard->release(currentKey);
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
	this->usbHidKeyboard->releaseAll();
}

#endif