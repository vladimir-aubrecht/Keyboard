#include "BluetoothFeature.h"

IKeyboardSDK* BluetoothFeature::keyboardSDK = NULL;
RGBLedFeature* BluetoothFeature::rgbLedFeature = NULL;

BluetoothFeature::BluetoothFeature(IKeyboardSDK* keyboardSDK, RGBLedFeature* rgbLedFeature)
{
    this->keyboardSDK = keyboardSDK;
    this->rgbLedFeature = rgbLedFeature;
}

void BluetoothFeature::toggleConnection()
{
    if (this->areFeaturesDisabled())
    {
        return;
    }

    this->blockFeatureProcessing();

    this->rgbLedFeature->enforceOff();

	this->keyboardSDK->GetActiveKeyboardDriver()->ResetState();

	if (((SelectiveKeyboardDriver*)keyboardSDK->GetActiveKeyboardDriver())->SwapKeyboards() == keyboardSDK->GetPrimaryKeyboardDriver())
	{
        this->keyboardSDK->GetActionEvaluator()->registerTemporaryTimerAction(
			1000, []()
			{ keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, 2, 0x00ffffff); },
			noTriggerKeyboardBlink);
	}
	else
	{
		this->keyboardSDK->GetActionEvaluator()->registerTemporaryTimerAction(
			1000, []()
			{ keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, 3, 0x00ffffff); },
			noTriggerKeyboardBlink);
	}
}

void BluetoothFeature::noTriggerKeyboardBlink()
{
    RGBLedFeature::rollbackPreviousLedStateEnforcement();
    BluetoothFeature::enableFeatureProcessing();
}

void BluetoothFeature::triggerReset()
{
    this->keyboardSDK->GetActiveKeyboardDriver()->ResetPairing();
}