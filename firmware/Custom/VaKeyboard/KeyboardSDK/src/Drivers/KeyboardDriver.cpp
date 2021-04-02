#include "KeyboardDriver.h"


KeyboardDriver::KeyboardDriver()
{
	Keyboard.begin();
}

void KeyboardDriver::SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, uint16_t** keymapProvider)
{
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			uint16_t currentKey = keymapProvider[row][column];

			bool isPressed = (pressedKeysMatrix->matrixData[row] >> column) & 1 == 1;
			bool isReleased = (releasedKeysMatrix->matrixData[row] >> column) & 1 == 1;

			if (isPressed)
			{
				Keyboard.press(currentKey);
			}
			else if (isReleased)
			{
				Keyboard.release(currentKey);
			}
		}
	}

	Keyboard.flush();
}