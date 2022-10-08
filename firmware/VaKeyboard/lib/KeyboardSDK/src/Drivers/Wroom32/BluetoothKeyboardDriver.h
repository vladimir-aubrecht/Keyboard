#pragma once
#ifdef WROOM32
#include "../IKeyboardDriver.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"
#include "Drivers/IBatteryDriver.h"
#include "IKeyboardDescriptor.h"
#include <BleKeyboard.h>
class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	//ILogger *logger;
	Matrix *currentStateMatrix = NULL;
	IBatteryDriver *batteryDriver = NULL;
	IKeyboardDescriptor *keyboardDescriptor = NULL;
	const uint8_t maxKeyCountInReport = 6;
	BleKeyboard* bleKeyboard = new BleKeyboard("VaKeyboard");
	char* GenerateCommandBytes(uint8_t modifier, uint8_t* keys);
	void SplitToArrayOf(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray, uint8_t innerArrayLength);
	bool SendKeypresses(uint8_t modificators, uint8_t *keys);
	bool SendRelease();
	uint8_t ScanForModificators(Matrix *matrix, KeyCode **keymapProvider);
	uint8_t ScanForPressedRegularKeys(Matrix *matrix, KeyCode **keymapProvider, uint8_t *foundKeys);
	Matrix *UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
public:
	BluetoothKeyboardDriver(IBatteryDriver *batteryDriver, IKeyboardDescriptor *keyboardDescriptor, ILogger *logger);
	virtual void Init();
	virtual void ResetPairing();
	virtual void ResetState();
	virtual bool SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);
};
#endif