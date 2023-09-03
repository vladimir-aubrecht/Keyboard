#pragma once
#include "IKeyboardSDK.h"
#include "BaseFeature.h"

enum RGBLedFeatures : uint8_t
{
    RGBLedTurnOn = 3,
    RGBLedTurnOff = 4,
    RGBLedToggle = 5,
    RGBLedRandomizeColors = 6,
    RGBLedShowBatteryLevel = 7
};

class RGBLedFeature : public BaseFeature
{
    private:
        IKeyboardSDK* keyboardSDK = NULL;

        void turnOff();
        void turnOn();
        void randomizeColors();
        void toggle();
        void showBatteryLevel();

    public:
        RGBLedFeature(IKeyboardSDK* keyboardSDK);

        virtual void evaluate(uint8_t featureId);
};