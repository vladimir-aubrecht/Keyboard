#include "RGBLedFeature.h"

RGBLedFeature::RGBLedFeature(IKeyboardSDK* keyboardSDK)
{
    this->keyboardSDK = keyboardSDK;
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

    case RGBLedFeatures::RGBLedToggle:
        this->toggle();
        break;

    case RGBLedFeatures::RGBLedRandomizeColors:
        this->randomizeColors();
        break;

    case RGBLedFeatures::RGBLedShowBatteryLevel:
        this->showBatteryLevel();
        break;

    default:
        break;
    }
}