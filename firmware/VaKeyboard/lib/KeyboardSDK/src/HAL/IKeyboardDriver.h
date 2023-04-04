#pragma once

#include <Arduino.h>
#include "Matrix/Matrix.h"
#include "KeyCodes.h"

class IKeyboardDriver
{
public:
	virtual void ResetPairing() = 0;
	virtual void ResetState() = 0;
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix) = 0;
};
