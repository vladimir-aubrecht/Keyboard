#include <Arduino.h>

#include "KeyboardSDK.h"
#include "Drivers/UsbHidKeyboardDriver.h"
#include "Drivers/BluetoothKeyboardDriver.h"
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/DisplayDriver.h"
#include "Drivers/PinDriver.h"
#include "Drivers/BatteryDriver.h"
#include "KeyMapProvider.h"
#include "Drivers/RgbLedDriver.h"
#include "Logger.h"

#include "Adafruit_BluefruitLE_SPI.h"

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;

ILogger *logger = NULL;
IPinDriver *pinDriver = NULL;
RgbLedDriver *rgbLedDriver = NULL;
SelectiveKeyboardDriver *keyboardDriver = NULL;
DisplayDriver *displayDriver = NULL;
MatrixScanner *matrixScanner = NULL;
MatrixEvaluator *matrixEvaluator = NULL;
KeyMapProvider *keymapProvider = NULL;
ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK *keyboard = NULL;
BatteryDriver *batteryDriver = NULL;

IKeyboardDriver *btKeyboardDriver = NULL;
IKeyboardDriver *usbKeyboardDriver = NULL;

bool enforcedDisabledLeds = false;

void triggerBtReset()
{
	logger->logDebug(F("Resetting BT pairing..."));
	keyboardDriver->ResetPairing();
}

void toggleLeds()
{
	logger->logDebug(F("Toggling LEDs..."));
	enforcedDisabledLeds = !rgbLedDriver->toggle();
}

void toggleConnection()
{
	enforcedDisabledLeds = true;
	rgbLedDriver->turnOff();

	if (keyboardDriver->SwapKeyboards() == usbKeyboardDriver)
	{
		actionEvaluator->registerTemporaryTimerAction(
			1000, []()
			{ rgbLedDriver->blink(0xff, 0, 2, 0x00ffffff); },
			[]()
			{ enforcedDisabledLeds = false; });
	}
	else
	{
		actionEvaluator->registerTemporaryTimerAction(
			1000, []()
			{ rgbLedDriver->blink(0xff, 0, 3, 0x00ffffff); },
			[]()
			{ enforcedDisabledLeds = false; });
	}
}

void randomizeColors()
{
	rgbLedDriver->randomizeColors();
}

void turnOnLeds()
{
	if (enforcedDisabledLeds)
	{
		return;
	}

	rgbLedDriver->turnOn();
}

void turnOffLeds()
{
	rgbLedDriver->turnOff();
}

void showBatteryLevel()
{
	enforcedDisabledLeds = true;
	turnOffLeds();

	actionEvaluator->registerTemporaryTimerAction(
		1000, []()
		{ rgbLedDriver->blink(0xff, 0, (batteryDriver->readBatteryLevel() / 10) + 1, 0x00ffffff); },
		[]()
		{ enforcedDisabledLeds = false; });
}

void setup()
{
	Serial.begin(115200);
	Wire.begin();

	logger = new Logger();
	batteryDriver = new BatteryDriver();
	rgbLedDriver = new RgbLedDriver(logger, numberOfRows, numberOfColumns);

	Wire.setClock(1700000L);

	pinDriver = new PinDriver(&Wire, logger);

	Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

	usbKeyboardDriver = new UsbHidKeyboardDriver();
	btKeyboardDriver = new BluetoothKeyboardDriver(ble, logger);

	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);

	// displayDriver = new DisplayDriver(&SPI);
	matrixScanner = new MatrixScanner(pinDriver, numberOfRows, numberOfColumns, logger);
	matrixEvaluator = new MatrixEvaluator();
	keymapProvider = new KeyMapProvider(numberOfRows, numberOfColumns);
	actionEvaluator = new ActionEvaluator(keymapProvider, logger);
	keyboard = new KeyboardSDK(matrixScanner, matrixEvaluator, keyboardDriver, keymapProvider, actionEvaluator, logger);

	actionEvaluator->registerMatrixAction(triggerBtReset, 3, new KeyboardKeycode[3]{KEY_ESC, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(toggleLeds, 3, new KeyboardKeycode[3]{KEY_F1, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(toggleConnection, 3, new KeyboardKeycode[3]{KEY_F2, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(randomizeColors, 3, new KeyboardKeycode[3]{KEY_F3, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(showBatteryLevel, 3, new KeyboardKeycode[3]{KEY_F4, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerTimerAction(90000UL, 0UL, turnOffLeds, turnOnLeds);

	// logger->logDebug(F("\nSetup is done!"));
}

void loop()
{
	keyboard->scan();
	uint8_t batteryLevel = batteryDriver->readBatteryLevel();

	if (batteryLevel < 15)
	{
		rgbLedDriver->setColor(0, 0, 0xff, 0, 0);
	}
}