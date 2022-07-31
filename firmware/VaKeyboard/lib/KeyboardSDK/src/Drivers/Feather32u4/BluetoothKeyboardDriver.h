#pragma once

#ifndef ARDUINO_MICRO

#include "../IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"

#include "Drivers/IBatteryDriver.h"

class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	Adafruit_BluefruitLE_SPI *ble;
	//ILogger *logger;
	Matrix *currentStateMatrix = NULL;
	IBatteryDriver *batteryDriver = NULL;
	const uint8_t maxKeyCountInReport = 6;

	String ConvertToHexCode(uint8_t code);
	void SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength);
	bool SendKeypresses(uint8_t modificators, uint8_t *keys);
	bool SendRelease();
	uint8_t ScanForModificators(Matrix *matrix, KeyboardKeycode **keymapProvider);
	uint8_t ScanForPressedRegularKeys(Matrix *matrix, KeyboardKeycode **keymapProvider, uint8_t *foundKeys);
	Matrix *UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

public:
	BluetoothKeyboardDriver(Adafruit_BluefruitLE_SPI *ble, IBatteryDriver *batteryDriver, ILogger *logger);

	virtual void Init();
	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider);
};

#endif