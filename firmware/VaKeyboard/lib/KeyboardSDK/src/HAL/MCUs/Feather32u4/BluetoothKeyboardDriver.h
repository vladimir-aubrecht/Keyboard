#pragma once

#ifdef FEATHER32U4

#include "HAL/IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"
#include "BaseKeyboardDescriptor.h"

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"

#include "HAL/IBatteryDriver.h"

class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	const char* AT_KEYBOARD_CODE = "AT+BLEKEYBOARDCODE=";

	static BluetoothKeyboardDriver* instance;

	Adafruit_BluefruitLE_SPI *ble;
	//ILogger *logger;
	Matrix *currentStateMatrix = NULL;
	IBatteryDriver *batteryDriver = NULL;
	BaseKeyboardDescriptor *keyboardDescriptor = NULL;
	const uint8_t maxKeyCountInReport = 6;

	char* GenerateCommandBytes(uint8_t modifier, uint8_t* keys);
	void SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength);
	bool SendKeypresses(uint8_t modificators, uint8_t *keys);
	bool SendRelease();
	uint8_t ScanForModificators(Matrix *matrix);
	uint8_t ScanForPressedRegularKeys(Matrix *matrix, KeyCode **keymap, uint8_t *foundKeys);
	Matrix *UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

public:
	BluetoothKeyboardDriver(Adafruit_BluefruitLE_SPI *ble, IBatteryDriver *batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);

	virtual void Init();
	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

	static BluetoothKeyboardDriver* Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger);
	static BluetoothKeyboardDriver* GetInstance();
};

#endif

