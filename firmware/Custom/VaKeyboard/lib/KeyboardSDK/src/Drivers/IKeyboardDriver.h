#pragma once

#include <Arduino.h>
#include "../Matrix/Matrix.h"
#include "KeyCodes.h"

class IKeyboardDriver
{
public:
	virtual void SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider) = 0;
};
