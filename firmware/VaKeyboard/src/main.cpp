#include <Arduino.h>

#include "KeyboardSDK.h"
#include "Matrix/MatrixDebouncer.h"
//#include "Drivers/DisplayDriver.h"
#include "Logger.h"

#ifdef NUMPAD
#include "Drivers/Numpad/KeyboardDescriptor.h"
#include "Drivers/Numpad/PinDriver.h"
#include "Drivers/Numpad/RgbLedDriver.h"

const uint8_t numberOfRows = 5;
const uint8_t numberOfColumns = 4;
#endif

#ifdef TKL
#include "Drivers/TKL/KeyboardDescriptor.h"
#include "Drivers/TKL/PinDriver.h"
#include "Drivers/TKL/RgbLedDriver.h"

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;
#endif

#ifdef FEATHER32U4
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/Feather32u4/BatteryDriver.h"
#include "Drivers/Feather32u4/UsbHidKeyboardDriver.h"
#include "Drivers/Feather32u4/BluetoothKeyboardDriver.h"
#include "Adafruit_BluefruitLE_SPI.h"
#endif

#ifdef ARDUINO_MICRO
#include "Drivers/Micro/BatteryDriver.h"
#include "Drivers/Micro/UsbHidKeyboardDriver.h"
#include "Chips/Max7301.h"
#endif

#ifdef PORTENTA_H7
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/PortentaH7/BatteryDriver.h"
#include "Drivers/PortentaH7/UsbHidKeyboardDriver.h"
#include "Drivers/PortentaH7/BluetoothKeyboardDriver.h"
#endif

#ifdef TINYS3
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/TinyS3/BatteryDriver.h"
#include "Drivers/TinyS3/UsbHidKeyboardDriver.h"
#include "Drivers/TinyS3/BluetoothKeyboardDriver.h"
#endif

#ifdef FEATHER_ESP32_S3_NOPSRAM
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/Feather_ESP32_S3_NOPSRAM/BatteryDriver.h"
#include "Drivers/Feather_ESP32_S3_NOPSRAM/UsbHidKeyboardDriver.h"
#include "Drivers/Feather_ESP32_S3_NOPSRAM/BluetoothKeyboardDriver.h"
#endif

#ifdef WROOM32
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/Wroom32/BatteryDriver.h"
#include "Drivers/Wroom32/UsbHidKeyboardDriver.h"
#include "Drivers/Wroom32/BluetoothKeyboardDriver.h"
#endif
#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused

RgbLedDriver *rgbLedDriver = NULL;
ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK *keyboard = NULL;
IBatteryDriver *batteryDriver = NULL;
IKeyboardDriver *usbKeyboardDriver = NULL;
USBHIDKeyboard usbHidKeyboard;

bool enforcedDisabledLeds = false;
bool isActionInProgress = false;

void resumeLeds()
{
	enforcedDisabledLeds = false;
	isActionInProgress = false;
}

#ifndef ARDUINO_MICRO
SelectiveKeyboardDriver *keyboardDriver = NULL;

bool triggerBtReset()
{
	// logger->logDebug(F("Resetting BT pairing..."));
	keyboardDriver->ResetPairing();

	return true;
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

#endif

bool toggleLeds()
{
	// logger->logDebug(F("Toggling LEDs..."));
	enforcedDisabledLeds = !rgbLedDriver->toggle();

	return true;
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
	delay(2000); // Keep the delay. It's useful when program crashes during the setup as you can reflash program without the need of pressing RESET button.

	Serial.begin(115200);
	Wire.begin();

	ILogger* logger = new NullLogger();
	batteryDriver = new BatteryDriver();
	rgbLedDriver = new RgbLedDriver(logger, numberOfRows, numberOfColumns);

	IKeyboardDescriptor* keyboardDescriptor = new KeyboardDescriptor(numberOfRows, numberOfColumns);

	usbKeyboardDriver = new UsbHidKeyboardDriver(keyboardDescriptor, &usbHidKeyboard);

#ifdef FEATHER32U4
	Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(ble, batteryDriver, keyboardDescriptor, logger);
	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);

	#ifdef NUMPAD
	IPinDriver* pinDriver = new PinDriver(new Max7301(11), logger);
	#endif

	#ifdef TKL
	IPinDriver* pinDriver = new PinDriver(&Wire, logger);
	#endif
#endif

#ifdef ARDUINO_MICRO
	IKeyboardDriver* keyboardDriver = usbKeyboardDriver;
	IPinDriver* pinDriver = new PinDriver(&Wire, logger);
#endif

#ifdef PORTENTA_H7
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(batteryDriver, keyboardDescriptor, logger);
	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);
	IPinDriver* pinDriver = new PinDriver(&Wire, logger);
#endif

#ifdef TINYS3
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(batteryDriver, keyboardDescriptor, logger);
	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);
	IPinDriver* pinDriver = new PinDriver(new Max7301(SS), logger);
#endif
#ifdef WROOM32
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(batteryDriver, keyboardDescriptor, logger);
	keyboardDriver = new SelectiveKeyboardDriver(btKeyboardDriver, usbKeyboardDriver);
	IPinDriver* pinDriver = new PinDriver(new Max7301(SS), logger);
#endif
#ifdef FEATHER_ESP32_S3_NOPSRAM
	IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(batteryDriver, keyboardDescriptor, logger);
	keyboardDriver = new SelectiveKeyboardDriver(usbKeyboardDriver, btKeyboardDriver);
	IPinDriver* pinDriver = new PinDriver(new Max7301(9, 6, 5, 10), logger);
#endif

	actionEvaluator = new ActionEvaluator(keyboardDescriptor, logger);
	keyboard = new KeyboardSDK(
		new MatrixScanner(pinDriver, numberOfRows, numberOfColumns, logger),
		new MatrixEvaluator(new MatrixDebouncer(keyboardDescriptor, 2)),
		keyboardDriver,
		keyboardDescriptor,
		actionEvaluator,
		logger);

	#ifdef TKL
	#ifndef ARDUINO_MICRO
	actionEvaluator->registerMatrixAction(callWithGuard<triggerBtReset>, 3, new KeyCode[3]{::KEY_ESC, ::KEY_LEFT_CTRL, ::KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleConnection>, 3, new KeyCode[3]{::KEY_F2, ::KEY_LEFT_CTRL, ::KEY_LEFT_GUI});
	#endif
	actionEvaluator->registerMatrixAction(callWithGuard<toggleLeds>, 3, new KeyCode[3]{::KEY_F1, ::KEY_LEFT_CTRL, ::KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<randomizeColors>, 3, new KeyCode[3]{::KEY_F3, ::KEY_LEFT_CTRL, ::KEY_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<showBatteryLevel>, 3, new KeyCode[3]{::KEY_F4, ::KEY_LEFT_CTRL, ::KEY_LEFT_GUI});
	actionEvaluator->registerTimerAction(90000UL, 0UL, callWithGuard<turnOffLeds>, callWithGuard<turnOnLeds>);
	#endif

	#ifdef NUMPAD
	actionEvaluator->registerMatrixAction(callWithGuard<triggerBtReset>, 2, new KeyCode[2]{::KEY_NUM_LOCK, ::KEYPAD_SUBTRACT});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleConnection>, 2, new KeyCode[2]{::KEY_NUM_LOCK, ::KEYPAD_1});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleLeds>, 2, new KeyCode[2]{::KEY_NUM_LOCK, ::KEYPAD_0});
	actionEvaluator->registerMatrixAction(callWithGuard<randomizeColors>, 2, new KeyCode[2]{::KEY_NUM_LOCK, ::KEYPAD_DOT});
	actionEvaluator->registerMatrixAction(callWithGuard<showBatteryLevel>, 2, new KeyCode[2]{::KEY_NUM_LOCK, ::KEYPAD_ENTER});
	actionEvaluator->registerTimerAction(90000UL, 0UL, callWithGuard<turnOffLeds>, callWithGuard<turnOnLeds>);
	#endif
	// logger->logDebug(F("\nSetup is done!"));
}

void loop()
{
	// max7301->begin();
	// max7301->write(0x09, 0x55);
	// Serial.println(max7301->read(0x09));

	// return;

	keyboard->scan();
	uint8_t batteryLevel = batteryDriver->readBatteryLevel();

	if (batteryLevel < 15)
	{
		rgbLedDriver->setColor(0, 0, 0xff, 0, 0);
	}
}