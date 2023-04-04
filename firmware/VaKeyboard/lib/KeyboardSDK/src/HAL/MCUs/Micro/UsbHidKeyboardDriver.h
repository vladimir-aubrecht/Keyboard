#pragma once

#ifdef ARDUINO_MICRO

#include "HAL/IKeyboardDriver.h"
#include "BaseKeyboardDescriptor.h"

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