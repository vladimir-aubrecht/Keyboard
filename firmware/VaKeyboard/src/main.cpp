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

KeyboardSDK* keyboardSDK = NULL;

void setup()
{
	delay(2000); // Keep the delay. It's useful when program crashes during the setup as you can reflash program without the need of pressing RESET button.

	Serial.begin(115200);
	Wire.begin();

	keyboardSDK = new KeyboardSDK(McuConfig::csPin, McuConfig::mosiPin, McuConfig::sclkPin, McuConfig::misoPin, &Wire);

	auto rgbLedFeature = new RGBLedFeature(keyboardSDK);
	auto bluetoothFeature = new BluetoothFeature(keyboardSDK);

	auto macroEvaluator = keyboardSDK->GetMacroEvaluator();
	macroEvaluator->registerFeature(rgbLedFeature);
	macroEvaluator->registerFeature(bluetoothFeature);
}

void loop()
{
	keyboardSDK->GetKeyPressProcessor()->scan();
	Serial.println("test\n");

	uint8_t batteryLevel = keyboardSDK->GetBatteryDriver()->readBatteryLevel();

	if (batteryLevel < 15)
	{
		keyboardSDK->GetRGBLedDriver()->setColor(0, 0, 0xff, 0, 0);
	}
}