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

ILogger* logger = new Logger();
PinDriver* pinDriver = new PinDriver(logger);
RgbLedDriver* rgbLedDriver = new RgbLedDriver(logger);

//TODO: Find better way of detecting capabilities and enabling includes
#ifndef ESP32
IKeyboardDriver* keyboardDriver = new UsbHidKeyboardDriver();
#else
IKeyboardDriver* keyboardDriver = new BluetoothKeyboardDriver();
#endif

DisplayDriver* displayDriver = new DisplayDriver();
MatrixScanner* matrixScanner = new MatrixScanner(pinDriver, numberOfRows, numberOfColumns);
MatrixEvaluator* matrixEvaluator = new MatrixEvaluator();
KeyMapProvider* keymapProvider = new KeyMapProvider(numberOfRows, numberOfColumns);

KeyboardSDK keyboard = KeyboardSDK(matrixScanner, matrixEvaluator, keyboardDriver, keymapProvider);

void setup()
{
	Serial.begin(9600);

	displayDriver->initialise();
	pinDriver->initialise();
	rgbLedDriver->initialise();

	Serial.println("\nSetup is done!");
}

void loop()
{
	keyboard.scan();
}