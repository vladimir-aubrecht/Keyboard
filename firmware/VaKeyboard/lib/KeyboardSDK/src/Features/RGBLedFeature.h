#pragma once
#include "IKeyboardSDK.h"
#include "BaseFeature.h"

enum RGBLedFeatures : uint8_t
{
    RGBLedTurnOn = 3,
    RGBLedTurnOff = 4,
    RGBLedToggle = 5,
    RGBLedRandomizeColors = 6,
    RGBLedShowBatteryLevel = 7,
    RGBLedBlinkBattery = 8,
    RGBLedResume = 9,
    RGBLedBlinkUSBSelection = 10,
    RGBLedBlinkBTSelection = 11,
    RGBLedDelayTurnOff = 13
};

class RGBLedFeature : public BaseFeature
{
    private:
        IKeyboardSDK* keyboardSDK = NULL;
        bool enforceDisabledLeds = false;
        bool previousEnforceDisabledLeds = false;
        unsigned long lastKeyPressTime = 0;

        void resume();

        void turnOff();
        void turnOn();
        void randomizeColors();
        void toggle();
        void showBatteryLevel();
        void blinkKey(uint8_t keyColumn);
        void enforceOff();
        void enforceOn();
        void rollbackPreviousLedStateEnforcement();

    public:
        RGBLedFeature(IKeyboardSDK* keyboardSDK);

        virtual void evaluate(uint8_t featureId, unsigned long activationTime, uint16_t duration);
};