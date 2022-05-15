#pragma once
#include "IKeyboardDriver.h"
#include "HID-Project.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
public:
	UsbHidKeyboardDriver();

	virtual void ResetPairing();
	virtual void SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider);
};