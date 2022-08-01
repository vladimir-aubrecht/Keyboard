#pragma once

#ifdef FEATHER32U4

#include "../IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"

#include "HID-Project.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	IKeyboardDescriptor *keyboardDescriptor = NULL;

public:
	UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif