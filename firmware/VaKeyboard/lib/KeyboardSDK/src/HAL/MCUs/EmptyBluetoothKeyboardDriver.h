#pragma once

#include "HAL/IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

#include "HAL/IBatteryDriver.h"
#include "BaseKeyboardDescriptor.h"


class BluetoothKeyboardDriver : public IKeyboardDriver
{

public:
	BluetoothKeyboardDriver(IBatteryDriver *batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);

	virtual void Init();
	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

	static BluetoothKeyboardDriver* Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);
	static BluetoothKeyboardDriver* GetInstance();
};