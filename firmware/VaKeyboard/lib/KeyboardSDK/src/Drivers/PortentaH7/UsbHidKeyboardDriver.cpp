#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver()
{
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider)
{
	bool isPress = false;
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			KeyboardKeycode currentKey = keymapProvider[row][column];

			bool isPressed = ((pressedKeysMatrix->matrixData[row] >> column) & 1) == 1;
			bool isReleased = ((releasedKeysMatrix->matrixData[row] >> column) & 1) == 1;

			if (isPressed)
			{
				isPress = true;
				
				//NKROKeyboard.press(currentKey);
			}
			else if (isReleased)
			{
				//NKROKeyboard.release(currentKey);
			}
		}
	}

	//NKROKeyboard.send();

	return isPress;
}

void UsbHidKeyboardDriver::ResetPairing()
{
}

void UsbHidKeyboardDriver::ResetState()
{
	//NKROKeyboard.releaseAll();
}