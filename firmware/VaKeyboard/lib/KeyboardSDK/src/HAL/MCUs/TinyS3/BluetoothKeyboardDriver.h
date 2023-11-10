#pragma once

#ifdef TINYS3

#include "HAL/IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

#include "HAL/IBatteryDriver.h"
#include "BaseKeyboardDescriptor.h"

#include <BleKeyboard.h>

class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	ILogger *logger;
	static BluetoothKeyboardDriver* instance;
	Matrix *currentStateMatrix = NULL;
	IBatteryDriver *batteryDriver = NULL;
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;
	const uint8_t maxKeyCountInReport = 6;
	BleKeyboard* bleKeyboard = NULL;

	void SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength);
	uint8_t ScanForPressedKeys(Matrix *matrix, KeyCode **keymapProvider, uint8_t *foundKeys, uint8_t *modificators);
	Matrix *UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

public:
	BluetoothKeyboardDriver(BleKeyboard* bleKeyboard, IBatteryDriver *batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);

	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

	static BluetoothKeyboardDriver* Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);
	static BluetoothKeyboardDriver* GetInstance();
};

#endif