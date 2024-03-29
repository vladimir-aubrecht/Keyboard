#pragma once

#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "HAL/IKeyboardDriver.h"
#include "BaseKeyboardDescriptor.h"

#include "USB.h"
#include "USBHIDKeyboard.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;

public:
	UsbHidKeyboardDriver(BaseKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif