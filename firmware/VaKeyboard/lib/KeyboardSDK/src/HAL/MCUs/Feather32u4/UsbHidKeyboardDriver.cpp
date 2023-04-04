#ifdef FEATHER32U4

#include "UsbHidKeyboardDriver.h"
#include "HID-Project.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;
	Consumer.begin();
	NKROKeyboard.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	bool isChanged = false;

	isKeyMenuHold |= this->keyboardDescriptor->getSelectedLayer(pressedKeysMatrix);
	isKeyMenuHold &= ~(this->keyboardDescriptor->getSelectedLayer(releasedKeysMatrix));

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
					isChanged = true;
					Consumer.press((ConsumerKeycode)currentKey);
				}
				else if (isReleased)
				{
					Consumer.release((ConsumerKeycode)currentKey);
					isChanged = true;
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
					isChanged = true;
				}
				else if (isReleased)
				{
					NKROKeyboard.release((KeyboardKeycode)currentKey);
					isChanged = true;
				}
			}
		}

		if (isChanged) {
			NKROKeyboard.send();
		}
	}
	return isChanged;
}

void UsbHidKeyboardDriver::ResetPairing()
{
}

void UsbHidKeyboardDriver::ResetState()
{
	NKROKeyboard.releaseAll();
}

#endif