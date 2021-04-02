#include "KeyboardSDK.h"
#include "Drivers/DisplayDriver.h"
#include "Drivers/PinDriver.h"
#include "KeyMapProvider.h"

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;

PinDriver pinDriver = PinDriver();
KeyboardDriver keyboardDriver = KeyboardDriver();
DisplayDriver displayDriver = DisplayDriver();
MatrixScanner matrixScanner = MatrixScanner(pinDriver, numberOfRows, numberOfColumns);
MatrixEvaluator matrixEvaluator = MatrixEvaluator();
KeyMapProvider keymapProvider = KeyMapProvider(numberOfRows, numberOfColumns);

KeyboardSDK keyboard = KeyboardSDK(matrixScanner, matrixEvaluator, keyboardDriver, keymapProvider);

void setup()
{
	Serial.begin(9600);

	displayDriver.initialise();
	pinDriver.initialise();

	Serial.println("\nSetup is done!");
}

void loop()
{
	keyboard.scan();
}