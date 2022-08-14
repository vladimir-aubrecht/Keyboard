#pragma once

#ifdef TINYS3

#include "../IKeyboardDriver.h"
#include "IKeyboardDescriptor.h"
#include "esp32-hal.h"
#include "esp32-hal-tinyusb.h"
#include "USB.h"

class UsbHidKeyboardDriver : public IKeyboardDriver
{
private:
	IKeyboardDescriptor *keyboardDescriptor = NULL;

private:
	uint8_t ScanForModificators(Matrix *matrix, KeyCode **keymapProvider);
	ESPUSB usb = ESPUSB();

public:
	UsbHidKeyboardDriver(IKeyboardDescriptor *keyboardDescriptor);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};

#endif