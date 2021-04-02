#include "KeyboardDriver.h"


KeyboardDriver::KeyboardDriver()
{

}

void KeyboardDriver::SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix)
{
	for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
		{
			uint16_t currentKey = keymap[row][column];

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