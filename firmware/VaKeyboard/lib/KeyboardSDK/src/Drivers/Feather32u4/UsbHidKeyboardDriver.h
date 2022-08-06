#pragma once

#ifdef FEATHER32U4

#include "../IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	IKeyboardDescriptor *keyboardDescriptor = NULL;
	bool isKeyMenuHold = false;	// Temporary hack, will be replaced by status matrix extracted from bluetooth keyboard one layer upper (matrix after debouncing is needed...)

public:
	UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif