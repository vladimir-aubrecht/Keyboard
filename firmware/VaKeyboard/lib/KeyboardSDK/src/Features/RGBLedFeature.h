#pragma once
#include "IKeyboardSDK.h"
#include "BaseFeature.h"

enum RGBLedFeatures : uint8_t
{
    RGBLedTurnOn = 3,
    RGBLedTurnOff = 4,
    RGBLedSuspend = 5,
    RGBLedRandomColors = 6,
    RGBLedBatteryLevel = 7,
    RGBLedToggle = 8,
    RGBLedWake = 9
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

        RGBLedFeatures currentState;
        RGBLedFeatures stateAtSuspend;

    public:
        RGBLedFeature(IKeyboardSDK* keyboardSDK);

        virtual void evaluate(uint8_t featureId);
};