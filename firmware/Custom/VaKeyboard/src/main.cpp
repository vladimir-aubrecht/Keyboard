#include <Arduino.h>

#include "KeyboardSDK.h"
#include "Drivers/KeyboardDriver.h"
#include "Drivers/BluetoothKeyboardDriver.h"
#include "Drivers/DisplayDriver.h"
#include "Drivers/PinDriver.h"
#include "KeyMapProvider.h"
#include "Drivers/RgbLedDriver.h"
#include "Logger.h"

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;

ILogger* logger = NULL;
IPinDriver* pinDriver = NULL;
RgbLedDriver* rgbLedDriver = NULL;
IKeyboardDriver* keyboardDriver = NULL;
DisplayDriver* displayDriver = NULL;
MatrixScanner* matrixScanner = NULL;
MatrixEvaluator* matrixEvaluator = NULL;
KeyMapProvider* keymapProvider = NULL;
KeyboardSDK* keyboard = NULL;

void setup()
{
	Serial.begin(115200);

	logger = new Logger();
	pinDriver = new PinDriver(logger);
	rgbLedDriver = new RgbLedDriver(logger);

	//TODO: Find better way of detecting capabilities and enabling includes
	#ifndef ESP32
	keyboardDriver = new UsbHidKeyboardDriver();
	#else
		#ifdef CONFIG_BT_ENABLED
	keyboardDriver = new BluetoothKeyboardDriver();
		#endif
	#endif

	//displayDriver = new DisplayDriver(&SPI);
	matrixScanner = new MatrixScanner(pinDriver, numberOfRows, numberOfColumns);
	matrixEvaluator = new MatrixEvaluator();
	keymapProvider = new KeyMapProvider(numberOfRows, numberOfColumns);
	keyboard = new KeyboardSDK(matrixScanner, matrixEvaluator, keyboardDriver, keymapProvider);

	Serial.println("\nSetup is done!");
}

void loop()
{
	keyboard->scan();
}