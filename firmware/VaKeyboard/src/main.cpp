#include <Arduino.h>

#include "KeyboardSDK.h"
#include "Matrix/MatrixDebouncer.h"
#include "Drivers/SelectiveKeyboardDriver.h"
//#include "Drivers/DisplayDriver.h"
#include "Drivers/TKL/PinDriver.h"
#include "Drivers/TKL/RgbLedDriver.h"
#include "KeyMapProvider.h"
#include "Logger.h"

#ifdef FEATHER32U4
#include "Drivers/Feather32u4/BatteryDriver.h"
#include "Drivers/Feather32u4/UsbHidKeyboardDriver.h"
#include "Drivers/Feather32u4/BluetoothKeyboardDriver.h"
#include "Adafruit_BluefruitLE_SPI.h"
#endif

#ifndef FEATHER32U4
#include "Drivers/PortentaH7/BatteryDriver.h"
#include "Drivers/PortentaH7/UsbHidKeyboardDriver.h"
#include "Drivers/PortentaH7/BluetoothKeyboardDriver.h"
#endif

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;

RgbLedDriver *rgbLedDriver = NULL;
SelectiveKeyboardDriver *keyboardDriver = NULL;
// DisplayDriver *displayDriver = NULL;
KeyMapProvider *keymapProvider = NULL;
ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK *keyboard = NULL;
IBatteryDriver *batteryDriver = NULL;

IKeyboardDriver *usbKeyboardDriver = NULL;

bool enforcedDisabledLeds = false;
bool isActionInProgress = false;

bool triggerBtReset()
{
	// logger->logDebug(F("Resetting BT pairing..."));
	keyboardDriver->ResetPairing();

	return true;
}

bool toggleLeds()
{
	// logger->logDebug(F("Toggling LEDs..."));
	enforcedDisabledLeds = !rgbLedDriver->toggle();

	return true;
}

void resumeLeds()
{
	enforcedDisabledLeds = false;
	isActionInProgress = false;
}

bool toggleConnection()
{
	// logger->logDebug(F("Toggling connection..."));

	enforcedDisabledLeds = true;
	rgbLedDriver->turnOff();
	keyboardDriver->ResetState();

	if (keyboardDriver->SwapKeyboards() == usbKeyboardDriver)
	{
		actionEvaluator->registerTemporaryTimerAction(
			1000, []()
			{ rgbLedDriver->blink(0xff, 0, 2, 0x00ffffff); },
			resumeLeds);
	}
	else
	{
		actionEvaluator->registerTemporaryTimerAction(
			1000, []()
			{ rgbLedDriver->blink(0xff, 0, 3, 0x00ffffff); },
			resumeLeds);
	}

	return false;
}

bool randomizeColors()
{
	// logger->logDebug(F("Toggling randomize colors..."));
	rgbLedDriver->randomizeColors();

	return true;
}

bool turnOnLeds()
{
	if (enforcedDisabledLeds)
	{
		return true;
	}

	// logger->logDebug(F("Toggling LEDs on..."));

	rgbLedDriver->turnOn();

	return true;
}

bool turnOffLeds()
{
	// logger->logDebug(F("Toggling LEDs off..."));
	rgbLedDriver->turnOff();

	return true;
}

bool showBatteryLevel()
{
	// logger->logDebug(F("Toggling show battery..."));

	enforcedDisabledLeds = true;
	turnOffLeds();

	actionEvaluator->registerTemporaryTimerAction(
		2000, []()
		{ rgbLedDriver->blink(0xff, 0, (batteryDriver->readBatteryLevel() / 10) + 1, 0x00ffffff); },
		resumeLeds);

	return false;
}

template <bool (*func)()>
void callWithGuard()
{
	if (isActionInProgress)
	{
		return;
	}
	isActionInProgress = true;

	if (func())
	{
		isActionInProgress = false;
	}
}

void setup()
{
	Serial.begin(115200);
	Wire.begin();

	ILogger* logger = new NullLogger();
	batteryDriver = new BatteryDriver();
	rgbLedDriver = new RgbLedDriver(logger, numberOfRows, numberOfColumns);

	usbKeyboardDriver = new UsbHidKeyboardDriver();

#ifdef FEATHER32U4
	Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(ble, batteryDriver, logger);
#else
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(batteryDriver, logger);
#endif

	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);

	// displayDriver = new DisplayDriver(&SPI);
	keymapProvider = new KeyMapProvider(numberOfRows, numberOfColumns);
	actionEvaluator = new ActionEvaluator(keymapProvider, logger);
	keyboard = new KeyboardSDK(
		new MatrixScanner(new PinDriver(&Wire, logger), numberOfRows, numberOfColumns, logger), 
		new MatrixEvaluator(new MatrixDebouncer(keymapProvider, 2)),
		keyboardDriver,
		keymapProvider,
		actionEvaluator,
		logger);

	actionEvaluator->registerMatrixAction(callWithGuard<triggerBtReset>, 3, new KeyboardKeycode[3]{KEY_ESC, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleLeds>, 3, new KeyboardKeycode[3]{KEY_F1, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleConnection>, 3, new KeyboardKeycode[3]{KEY_F2, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<randomizeColors>, 3, new KeyboardKeycode[3]{KEY_F3, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<showBatteryLevel>, 3, new KeyboardKeycode[3]{KEY_F4, KEY_LEFT_CTRL, KEY_LEFT_GUI});
	actionEvaluator->registerTimerAction(90000UL, 0UL, callWithGuard<turnOffLeds>, callWithGuard<turnOnLeds>);
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