#pragma once
#include "IKeyboardDriver.h"
#include "HID-Project.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:

public:
	UsbHidKeyboardDriver();

	virtual void SendKeys(Matrix* scannedKeysMatrix, Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, KeyboardKeycode** keymapProvider);
};