#pragma once

#include <Arduino.h>
#include "../Matrix/Matrix.h"

class IKeyboardDriver
{
public:
	virtual void SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, uint16_t** keymapProvider) = 0;
};

