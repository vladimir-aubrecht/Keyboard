#pragma once

#ifdef PORTENTA_H7

#include "HAL/IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

#include "HAL/IBatteryDriver.h"
#include "BaseKeyboardDescriptor.h"

#include "Mbed_BLE_HID.h"
//#include "services/HIDKeyboardService.h"


class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	static BluetoothKeyboardDriver* instance;
	//ILogger *logger;
	Matrix *currentStateMatrix = NULL;
	IBatteryDriver *batteryDriver = NULL;
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;
	const uint8_t maxKeyCountInReport = 6;

	String ConvertToHexCode(uint8_t code);
	void SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength);
	bool SendKeypresses(uint8_t modificators, uint8_t *keys);
	bool SendRelease();
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