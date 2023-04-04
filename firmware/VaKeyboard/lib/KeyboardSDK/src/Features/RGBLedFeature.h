#pragma once
#include "IKeyboardSDK.h"
#include "BaseFeature.h"

class RGBLedFeature : public BaseFeature
{
    private:
        static IKeyboardSDK* keyboardSDK;   // ActionEvaluator needs to be redesigned to get rid off function pointers to get rid off this static
        static bool enforceDisabledLeds;    // ActionEvaluator needs to be redesigned to get rid off function pointers to get rid off this static
        static bool previousEnforceDisabledLeds;    // ActionEvaluator needs to be redesigned to get rid off function pointers to get rid off this static

        static void triggerBatteryBlink();
        static void noTriggerBatteryBlink();


    public:
        RGBLedFeature(IKeyboardSDK* keyboardSDK);

        void turnOff();
        void turnOn();
        void randomizeColors();
        void toggle();
        void showBatteryLevel();
        void enforceOff();
        void enforceOn();
        static void rollbackPreviousLedStateEnforcement();
};