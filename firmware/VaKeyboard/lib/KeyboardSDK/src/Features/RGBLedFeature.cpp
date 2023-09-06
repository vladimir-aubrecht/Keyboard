#include "RGBLedFeature.h"

RGBLedFeature::RGBLedFeature(IKeyboardSDK* keyboardSDK)
{
    this->keyboardSDK = keyboardSDK;
    this->currentState = RGBLedFeatures::RGBLedTurnOn;
}

void RGBLedFeature::turnOff()
{
    this->keyboardSDK->GetRGBLedDriver()->turnOff();
}

void RGBLedFeature::turnOn()
{
    this->keyboardSDK->GetRGBLedDriver()->turnOn();
}

void RGBLedFeature::randomizeColors()
{
    this->keyboardSDK->GetRGBLedDriver()->randomizeColors();
}

void RGBLedFeature::toggle()
{
    this->keyboardSDK->GetRGBLedDriver()->toggle();
}

void RGBLedFeature::showBatteryLevel()
{
    this->turnOff();
    keyboardSDK->GetRGBLedDriver()->blink(0xff, 0, ( keyboardSDK->GetBatteryDriver()->readBatteryLevel() / 10) + 1, 0x00ffffff); 
}

void RGBLedFeature::evaluate(uint8_t featureId)
{
    switch (featureId)
    {
    case RGBLedFeatures::RGBLedTurnOn:
        this->turnOn();
        break;

    case RGBLedFeatures::RGBLedTurnOff:
        this->turnOff();
        break;

    case RGBLedFeatures::RGBLedRandomColors:
        this->randomizeColors();
        break;

    case RGBLedFeatures::RGBLedBatteryLevel:
        this->showBatteryLevel();
        break;

    case RGBLedFeatures::RGBLedToggle:
        this->toggle();
        break;

    case RGBLedFeatures::RGBLedSuspend:
        if (this->currentState != RGBLedFeatures::RGBLedSuspend)
        {
            this->stateAtSuspend = this->currentState;
            this->turnOff();
        }
        break;

    case RGBLedFeatures::RGBLedWake:
        if (this->currentState == RGBLedFeatures::RGBLedSuspend)
        {
            this->evaluate(this->stateAtSuspend);
            return;
        }
        break;

    default:
        break;
    }

    if (featureId != RGBLedFeatures::RGBLedWake)
    {
        this->currentState = (RGBLedFeatures)featureId;
    }
}