#pragma once

#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "../IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"

#include "USB.h"
#include "USBHIDKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	IKeyboardDescriptor *keyboardDescriptor = NULL;
	USBHIDKeyboard* usbHidKeyboard = NULL;

public:
	UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor, USBHIDKeyboard*);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif