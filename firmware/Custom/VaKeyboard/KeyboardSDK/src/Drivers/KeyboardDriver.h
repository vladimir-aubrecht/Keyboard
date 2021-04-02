#ifndef _KEYBOARDDRIVER_h
#define _KEYBOARDDRIVER_h

#include <arduino.h>
#include <Keyboard.h>
#include "../Matrix/Matrix.h"

class KeyboardDriver
{
public:
	KeyboardDriver();

	void SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, uint16_t** keymap);
};

#endif

