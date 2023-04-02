#pragma once

#ifdef TINYS2

#include "../IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"
#include "USB.h"
#include "USBHIDKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	IKeyboardDescriptor *keyboardDescriptor = NULL;
	USBHIDKeyboard* keyboard = NULL;

private:
	uint8_t ScanForModificators(Matrix *matrix, KeyCode **keymapProvider);

public:
	UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif