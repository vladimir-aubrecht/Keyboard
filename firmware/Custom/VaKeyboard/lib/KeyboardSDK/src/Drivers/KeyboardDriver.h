#pragma once
#include "IKeyboardDriver.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
public:
	UsbHidKeyboardDriver();

	virtual void SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, uint16_t** keymapProvider);
};