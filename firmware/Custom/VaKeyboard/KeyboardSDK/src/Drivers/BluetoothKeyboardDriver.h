#pragma once

#ifdef ESP32

#include "IKeyboardDriver.h"
#include <BleKeyboard.h>

class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	BleKeyboard* bleKeyboard;

public:
	BluetoothKeyboardDriver();

	virtual void SendKeys(Matrix* pressedKeysMatrix, Matrix* releasedKeysMatrix, uint16_t** keymapProvider);
};

#else
#pragma message "Detected not ESP32, skipping compilation of BluetoothKeyboardDriver as don't know if device has bluetooth."
#endif