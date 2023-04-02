#include <Arduino.h>

#include "Drivers/SelectiveKeyboardDriver.h"

#if defined(NUMPAD) && defined(V2)
#include "Drivers/TKL/V1/KeyboardSDK.h"
#endif

#if defined(TKL) && defined(V1)
#include "Drivers/TKL/V1/KeyboardSDK.h"
#endif

#if defined(TKL) && defined(V2)
#include "Drivers/TKL/V2/KeyboardSDK.h"
#endif

ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK* keyboardSDK = NULL;

bool enforcedDisabledLeds = false;
bool isActionInProgress = false;

void resumeLeds()
{
	enforcedDisabledLeds = false;
	isActionInProgress = false;
}

#ifndef ARDUINO_MICRO

bool triggerBtReset()
{
	// logger->logDebug(F("Resetting BT pairing..."));
	keyboardSDK->GetActiveKeyboardDriver()->ResetPairing();

	return true;
}

bool toggleConnection()
{
	// logger->logDebug(F("Toggling connection..."));

	enforcedDisabledLeds = true;
	keyboardSDK->GetRGBLedDriver()->turnOff();
	keyboardSDK->GetActiveKeyboardDriver()->ResetState();

	if (((SelectiveKeyboardDriver*)keyboardSDK->GetActiveKeyboardDriver())->SwapKeyboards() == keyboardSDK->GetPrimaryKeyboardDriver())
	{
		actionEvaluator->registerTemporaryTimerAction(
			1000, []()
			{ keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, 2, 0x00ffffff); },
			resumeLeds);
	}
	else
	{
		actionEvaluator->registerTemporaryTimerAction(
			1000, []()
			{ keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, 3, 0x00ffffff); },
			resumeLeds);
	}

	return false;
}

#endif

bool toggleLeds()
{
	// logger->logDebug(F("Toggling LEDs..."));
	enforcedDisabledLeds = !keyboardSDK->GetRGBLedDriver()->toggle();

	return true;
}

bool randomizeColors()
{
	// logger->logDebug(F("Toggling randomize colors..."));
	keyboardSDK->GetRGBLedDriver()->randomizeColors();

	return true;
}

bool turnOnLeds()
{
	if (enforcedDisabledLeds)
	{
		return true;
	}

	// logger->logDebug(F("Toggling LEDs on..."));

	keyboardSDK->GetRGBLedDriver()->turnOn();

	return true;
}

bool turnOffLeds()
{
	// logger->logDebug(F("Toggling LEDs off..."));
	keyboardSDK->GetRGBLedDriver()->turnOff();

	return true;
}

bool showBatteryLevel()
{
	// logger->logDebug(F("Toggling show battery..."));

	enforcedDisabledLeds = true;
	turnOffLeds();

	actionEvaluator->registerTemporaryTimerAction(
		2000, []()
		{ keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, ( keyboardSDK->GetBatteryDriver()->readBatteryLevel() / 10) + 1, 0x00ffffff); },
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

	#if defined(ARDUINO_MICRO)
	keyboardSDK = new KeyboardSDK(&Wire);
	#endif

	#if defined(FEATHER_ESP32_S3_NOPSRAM)
		keyboardSDK = new KeyboardSDK(0x70, 9, 6, 5, 10, &Wire);
	#endif

	#if defined(FEATHER32U4)
		keyboardSDK = new KeyboardSDK(0x70, 11, 10, 9, 13, &Wire);
	#endif
	
	#if defined(TINYS2)
		keyboardSDK = new KeyboardSDK(0x70, (uint8_t)14U, MOSI, SCK, MISO, &Wire);
	#endif

	actionEvaluator = keyboardSDK->GetActionEvaluator();

	#ifdef TKL
	#ifndef ARDUINO_MICRO
	actionEvaluator->registerMatrixAction(callWithGuard<triggerBtReset>, 3, new KeyCode[3]{::KK_ESC, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleConnection>, 3, new KeyCode[3]{::KK_F2, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	#endif
	actionEvaluator->registerMatrixAction(callWithGuard<toggleLeds>, 3, new KeyCode[3]{::KK_F1, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<randomizeColors>, 3, new KeyCode[3]{::KK_F3, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	actionEvaluator->registerMatrixAction(callWithGuard<showBatteryLevel>, 3, new KeyCode[3]{::KK_F4, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	actionEvaluator->registerTimerAction(90000UL, 0UL, callWithGuard<turnOffLeds>, callWithGuard<turnOnLeds>);
	#endif

	#ifdef NUMPAD
	actionEvaluator->registerMatrixAction(callWithGuard<triggerBtReset>, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_SUBTRACT});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleConnection>, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_1});
	actionEvaluator->registerMatrixAction(callWithGuard<toggleLeds>, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_0});
	actionEvaluator->registerMatrixAction(callWithGuard<randomizeColors>, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_DOT});
	actionEvaluator->registerMatrixAction(callWithGuard<showBatteryLevel>, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_ENTER});
	actionEvaluator->registerTimerAction(90000UL, 0UL, callWithGuard<turnOffLeds>, callWithGuard<turnOnLeds>);
	#endif
	// logger->logDebug(F("\nSetup is done!"));
}

void loop()
{
	keyboardSDK->GetKeyPressProcessor()->scan();

	uint8_t batteryLevel = keyboardSDK->GetBatteryDriver()->readBatteryLevel();

	if (batteryLevel < 15)
	{
		keyboardSDK->GetRGBLedDriver()->setColor(0, 0, 0xff, 0, 0);
	}
}