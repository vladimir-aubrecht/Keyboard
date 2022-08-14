#pragma once

#ifdef TINYS3

#include "../IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	IKeyboardDescriptor *keyboardDescriptor = NULL;

private:
	uint8_t ScanForModificators(Matrix *matrix, KeyCode **keymapProvider);

public:
	UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif