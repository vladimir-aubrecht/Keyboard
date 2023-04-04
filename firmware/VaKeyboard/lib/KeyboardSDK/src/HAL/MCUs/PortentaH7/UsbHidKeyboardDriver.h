#pragma once

#ifdef PORTENTA_H7

#include "HAL/IKeyboardDriver.h"
#include "BaseKeyboardDescriptor.h"


#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	USBKeyboard Keyboard;
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;

private:
	uint8_t ScanForModificators(Matrix *matrix, KeyCode **keymapProvider);

public:
	UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif