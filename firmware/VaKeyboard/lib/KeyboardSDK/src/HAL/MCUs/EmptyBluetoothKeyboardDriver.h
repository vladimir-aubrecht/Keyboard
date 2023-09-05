#pragma once

#include "HAL/IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

#include "HAL/IBatteryDriver.h"
#include "BaseKeyboardDescriptor.h"


class EmptyBluetoothKeyboardDriver : public IKeyboardDriver
{

public:
	EmptyBluetoothKeyboardDriver();

	virtual void Init();
	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

	static EmptyBluetoothKeyboardDriver* Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);
	static EmptyBluetoothKeyboardDriver* GetInstance();
};