#ifdef TINYS3

#include "UsbHidKeyboardDriver.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDSystemControl.h"

USBHIDKeyboard keyboard;
USBHIDConsumerControl ConsumerControl;
USBHIDSystemControl SystemControl;


UsbHidKeyboardDriver::UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor)
{
	this->keyboardDescriptor = keyboardDescriptor;

	// Important, default is just self powered and without this line it's not possible to wake up computer from sleep
	USB.usbAttributes(TUSB_DESC_CONFIG_ATT_SELF_POWERED | TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP);

	keyboard.begin();	
	ConsumerControl.begin();
	USB.begin();
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	isKeyMenuHold |= this->keyboardDescriptor->getSelectedLayer(pressedKeysMatrix);
	isKeyMenuHold &= ~(this->keyboardDescriptor->getSelectedLayer(releasedKeysMatrix));
	uint8_t currentLayer = isKeyMenuHold ? 1 : 0;

	auto keymap = this->keyboardDescriptor->getKeyMap()[currentLayer];

	bool isPress = false;
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			auto currentKey = keymap[row][column];

			uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
			uint8_t isReleased = releasedKeysMatrix->getBit(row, column);

			auto keyType = this->keyboardDescriptor->getKeyType(currentLayer, row, column);

			if (isPressed)
			{
				isPress = true;

				SystemControl.press(SYSTEM_CONTROL_WAKE_HOST);	//TODO: call this only when computer is on sleep...

				if (keyType != KeyType::MEDIA)
				{
					keyboard.pressRaw((uint8_t)currentKey);
				}
				else
				{
					ConsumerControl.press((uint8_t)currentKey);
				}
			}
			else if (isReleased)
			{
				keyboard.releaseRaw((uint8_t)currentKey);
				ConsumerControl.release();
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
	keyboard.begin();	
	ConsumerControl.begin();
	USB.begin();
	keyboard.releaseAll();
	ConsumerControl.release();
}

#endif