#pragma once

#ifdef PORTENTA_H7

#include "HAL/IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"


#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	USBKeyboard Keyboard;
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