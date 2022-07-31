#ifdef PORTENTA_H7

#include "UsbHidKeyboardDriver.h"

UsbHidKeyboardDriver::UsbHidKeyboardDriver()
{
}

bool UsbHidKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider)
{
	uint8_t modifiers = this->ScanForModificators(pressedKeysMatrix, keymapProvider);

	bool isPress = false;
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			KeyboardKeycode currentKey = keymapProvider[row][column];

			bool isPressed = ((pressedKeysMatrix->matrixData[row] >> column) & 1) == 1;

			if (isPressed && currentKey < 0xE0) // without modificator keys, 0xE0 starts modificator key
			{
				isPress = true;
				
				this->Keyboard.key_code(currentKey, modifiers);
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
}

uint8_t UsbHidKeyboardDriver::ScanForModificators(Matrix *matrix, KeyboardKeycode **keymapProvider)
{
	uint8_t modificators = 0;

	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			KeyboardKeycode currentKey = keymapProvider[row][column];

			bool isScannedPress = (matrix->matrixData[row] >> column) & 1 == 1;

			if (isScannedPress)
			{
				if (currentKey >= 0xE0) // modificator keys
				{
					uint8_t bit = (1 << (currentKey - 0xE0));
					modificators |= bit;
				}
			}
		}
	}
}

#endif