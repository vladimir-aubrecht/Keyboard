#include "RGBLedFeature.h"

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
    
    this->keyboardSDK->GetRGBLedDriver()->turnOn();
}

void RGBLedFeature::enforceOff()
{
    this->previousEnforceDisabledLeds = this->enforceDisabledLeds;
    this->enforceDisabledLeds = true;

    this->keyboardSDK->GetRGBLedDriver()->turnOff();
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

    this->keyboardSDK->GetFeatureScheduller()->setTtlSinceTime(RGBLedFeatures::RGBLedBlinkBattery, millis(), 2000);
    this->keyboardSDK->GetFeatureScheduller()->setActivationTime(RGBLedFeatures::RGBLedResume, millis() + 2000);
}

void RGBLedFeature::blinkKey(uint8_t keyColumn)
{
    this->enforceOff();

    keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, keyColumn, 0x00ffffff);
}

void RGBLedFeature::rollbackPreviousLedStateEnforcement()
{
    enforceDisabledLeds = previousEnforceDisabledLeds;
}

void RGBLedFeature::resume()
{
    RGBLedFeature::rollbackPreviousLedStateEnforcement();
    RGBLedFeature::enableFeatureProcessing();
}

void RGBLedFeature::evaluate(uint8_t featureId, unsigned long activationTime, uint16_t duration)
{
    switch (featureId)
    {
    case RGBLedFeatures::RGBLedTurnOn:
        this->turnOn();
        break;

    case RGBLedFeatures::RGBLedTurnOff:
        this->turnOn();
        break;

    case RGBLedFeatures::RGBLedToggle:
        this->toggle();
        break;

    case RGBLedFeatures::RGBLedRandomizeColors:
        this->randomizeColors();
        break;

    case RGBLedFeatures::RGBLedShowBatteryLevel:
        this->showBatteryLevel();
        break;

    case RGBLedFeatures::RGBLedBlinkBattery:
        keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, ( keyboardSDK->GetBatteryDriver()->readBatteryLevel() / 10) + 1, 0x00ffffff); 
        break;

    case RGBLedFeatures::RGBLedResume:
        this->resume();
        break;

    case RGBLedFeatures::RGBLedBlinkUSBSelection:
        this->blinkKey(2);
        break;

    case RGBLedFeatures::RGBLedBlinkBTSelection:
        this->blinkKey(3);
        break;

    case BaseFeatures::BaseKeyPress:
        lastKeyPressTime = millis();
        break;

    case RGBLedFeatures::RGBLedDelayTurnOff:
        if (lastKeyPressTime > 0)
        {
            if (this->lastKeyPressTime + duration < millis())
            {
                enforceOff();
            }
            else
            {
                enforceOn();
            }

            this->keyboardSDK->GetFeatureScheduller()->setActivationTime(RGBLedFeatures::RGBLedTurnOff, this->lastKeyPressTime + duration);
        }
        break;
    
    default:
        break;
    }
}