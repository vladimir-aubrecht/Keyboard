#include <Arduino.h>

#if defined(NUMPAD) && defined(V2)
#include "Drivers/Numpad/V2/KeyboardSDK.h"
#endif

#if defined(TKL) && defined(V1)
#include "Drivers/TKL/V1/KeyboardSDK.h"
#endif

#if defined(TKL) && defined(V2)
#include "Drivers/TKL/V2/KeyboardSDK.h"
#endif

#include "Features/BluetoothFeature.h"
#include "Features/RGBLedFeature.h"

ActionEvaluator *actionEvaluator = NULL;
KeyboardSDK* keyboardSDK = NULL;

BluetoothFeature* bluetoothFeature = NULL;
RGBLedFeature* rgbLedFeature = NULL;

void triggerBtReset()
{
	bluetoothFeature->triggerReset();
}

void toggleConnection()
{
	bluetoothFeature->toggleConnection();
}

void toggleLeds()
{
	rgbLedFeature->toggle();
}

void randomizeColors()
{
	rgbLedFeature->randomizeColors();
}

void turnOnLeds()
{
	rgbLedFeature->turnOn();
}

void turnOffLeds()
{
	rgbLedFeature->turnOff();
}

void showBatteryLevel()
{
	rgbLedFeature->showBatteryLevel();
}

void setup()
{
	delay(2000); // Keep the delay. It's useful when program crashes during the setup as you can reflash program without the need of pressing RESET button.

	Serial.begin(115200);
	Wire.begin();

	keyboardSDK = new KeyboardSDK(McuConfig::csPin, McuConfig::mosiPin, McuConfig::sclkPin, McuConfig::misoPin, &Wire);

	rgbLedFeature = new RGBLedFeature(keyboardSDK);
	bluetoothFeature = new BluetoothFeature(keyboardSDK, rgbLedFeature);

	actionEvaluator = keyboardSDK->GetActionEvaluator();


	#ifdef TKL

	if (BluetoothKeyboardDriver::GetInstance() != NULL) {
		actionEvaluator->registerMatrixAction(triggerBtReset, 3, new KeyCode[3]{::KK_ESC, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
		actionEvaluator->registerMatrixAction(toggleConnection, 3, new KeyCode[3]{::KK_F2, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	}

	actionEvaluator->registerMatrixAction(toggleLeds, 3, new KeyCode[3]{::KK_F1, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	actionEvaluator->registerMatrixAction(randomizeColors, 3, new KeyCode[3]{::KK_F3, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	actionEvaluator->registerMatrixAction(showBatteryLevel, 3, new KeyCode[3]{::KK_F4, ::KK_LEFT_CTRL, ::KK_LEFT_GUI});
	//actionEvaluator->registerTimerAction(90000UL, 0UL, turnOffLeds, turnOnLeds);
	#endif

	#ifdef NUMPAD
	actionEvaluator->registerMatrixAction(triggerBtReset, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_SUBTRACT});
	actionEvaluator->registerMatrixAction(toggleConnection, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_1});
	actionEvaluator->registerMatrixAction(toggleLeds, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_0});
	actionEvaluator->registerMatrixAction(randomizeColors, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_PAD_DOT});
	actionEvaluator->registerMatrixAction(showBatteryLevel, 2, new KeyCode[2]{::KK_NUM_LOCK, ::KK_ENTER});
	actionEvaluator->registerTimerAction(90000UL, 0UL, turnOffLeds>, turnOnLeds);
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