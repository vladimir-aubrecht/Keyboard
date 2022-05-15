#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver()
{
	NKROKeyboard.begin();
}

void UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider)
{
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			KeyboardKeycode currentKey = keymapProvider[row][column];

			bool isPressed = ((pressedKeysMatrix->matrixData[row] >> column) & 1) == 1;
			bool isReleased = ((releasedKeysMatrix->matrixData[row] >> column) & 1) == 1;

			if (isPressed)
			{
				NKROKeyboard.press(currentKey);
			}
			else if (isReleased)
			{
				NKROKeyboard.release(currentKey);
			}
		}
	}

	NKROKeyboard.send();
}

void UsbHidKeyboardDriver::ResetPairing()
{
}

void UsbHidKeyboardDriver::ResetState()
{
	NKROKeyboard.releaseAll();
}