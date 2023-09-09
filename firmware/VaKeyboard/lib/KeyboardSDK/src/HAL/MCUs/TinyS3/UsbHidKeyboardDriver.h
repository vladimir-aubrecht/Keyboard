#pragma once

#ifdef TINYS3

#include "HAL/IKeyboardDriver.h"
#include "BaseKeyboardDescriptor.h"
#include "USB.h"
#include "USBHIDKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;
	bool isKeyMenuHold = false;	// Temporary hack, will be replaced by status matrix extracted from bluetooth keyboard one layer upper (matrix after debouncing is needed...)

public:
	UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif