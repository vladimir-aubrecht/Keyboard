#pragma once

#ifdef ARDUINO_MICRO

#include "../IKeyboardDriver.h"

#include "HID-Project.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
public:
	UsbHidKeyboardDriver();

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider);
};

#endif