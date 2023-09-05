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
	//ILogger *logger;
	static BluetoothKeyboardDriver* instance;
	Matrix *currentStateMatrix = NULL;
	IBatteryDriver *batteryDriver = NULL;
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;
	const uint8_t maxKeyCountInReport = 6;
	BleKeyboard* bleKeyboard = NULL;

	String ConvertToHexCode(uint8_t code);
	void SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength);
	uint8_t ScanForModificators(Matrix *matrix, KeyCode **keymapProvider);
	uint8_t ScanForPressedRegularKeys(Matrix *matrix, KeyCode **keymapProvider, uint8_t *foundKeys);
	Matrix *UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

public:
	BluetoothKeyboardDriver(IBatteryDriver *batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);

	virtual void Init();
	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

	static BluetoothKeyboardDriver* Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);
	static BluetoothKeyboardDriver* GetInstance();
};

#endif