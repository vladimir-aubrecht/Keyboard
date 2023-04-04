#include "RGBLedFeature.h"

IKeyboardSDK* RGBLedFeature::keyboardSDK = NULL;
bool RGBLedFeature::enforceDisabledLeds = false;
bool RGBLedFeature::previousEnforceDisabledLeds = false;

RGBLedFeature::RGBLedFeature(IKeyboardSDK* keyboardSDK)
{
    this->keyboardSDK = keyboardSDK;
}

void RGBLedFeature::turnOff()
{
    if (this->areFeaturesDisabled())
    {
        return;
    }

    this->keyboardSDK->GetRGBLedDriver()->turnOff();
}

void RGBLedFeature::turnOn()
{
    if (this->areFeaturesDisabled() || this->enforceDisabledLeds)
    {
        return;
    }

    this->keyboardSDK->GetRGBLedDriver()->turnOn();
}

void RGBLedFeature::enforceOn()
{
    this->previousEnforceDisabledLeds = this->enforceDisabledLeds;
    this->enforceDisabledLeds = false;
    this->turnOn();
}

void RGBLedFeature::enforceOff()
{
    this->previousEnforceDisabledLeds = this->enforceDisabledLeds;
    this->enforceDisabledLeds = true;
    this->turnOff();
}

void RGBLedFeature::randomizeColors()
{
    if (this->areFeaturesDisabled())
    {
        return;
    }

    this->keyboardSDK->GetRGBLedDriver()->randomizeColors();
}

void RGBLedFeature::toggle()
{
    if (this->areFeaturesDisabled())
    {
        return;
    }

    this->previousEnforceDisabledLeds = this->enforceDisabledLeds;
    this->enforceDisabledLeds = !this->keyboardSDK->GetRGBLedDriver()->toggle();
}

void RGBLedFeature::showBatteryLevel()
{
    if (this->areFeaturesDisabled())
    {
        return;
    }

    this->blockFeatureProcessing();

    enforceOff();

	this->keyboardSDK->GetActionEvaluator()->registerTemporaryTimerAction(2000, triggerBatteryBlink, noTriggerBatteryBlink);
}

void RGBLedFeature::triggerBatteryBlink()
{
    keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, ( keyboardSDK->GetBatteryDriver()->readBatteryLevel() / 10) + 1, 0x00ffffff); 
}

void RGBLedFeature::rollbackPreviousLedStateEnforcement()
{
    enforceDisabledLeds = previousEnforceDisabledLeds;
}

void RGBLedFeature::noTriggerBatteryBlink()
{
    RGBLedFeature::rollbackPreviousLedStateEnforcement();
    RGBLedFeature::enableFeatureProcessing();
}

