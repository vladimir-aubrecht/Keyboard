#pragma once

#include "IKeyboardDriver.h"

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"

class BluetoothKeyboardDriver : public IKeyboardDriver
{
private:
	Adafruit_BluefruitLE_SPI *ble;
	Matrix *currentStateMatrix = NULL;

	String ConvertToHexCode(uint8_t code);
	void SplitToArrayOf5(uint8_t *array, uint8_t arrayLength, uint8_t **outputArray);
	bool SendKeypresses(uint8_t modificators, uint8_t keys[5]);
	bool SendRelease();
	uint8_t ScanForModificators(Matrix *matrix, KeyboardKeycode **keymapProvider);
	uint8_t ScanForPressedRegularKeys(Matrix *matrix, KeyboardKeycode **keymapProvider, uint8_t *foundKeys);
	Matrix *UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix);

public:
	BluetoothKeyboardDriver(Adafruit_BluefruitLE_SPI *ble);

	virtual void SendKeys(Matrix *scannedKeysMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider);
};
