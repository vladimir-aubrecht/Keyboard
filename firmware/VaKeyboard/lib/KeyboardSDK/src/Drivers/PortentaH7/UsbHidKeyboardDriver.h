#pragma once
#include "../IKeyboardDriver.h"

//#include "PluggableUSBHID.h"
//#include "USBKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
//USBKeyboard Keyboard;

public:
	UsbHidKeyboardDriver();

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider);
};