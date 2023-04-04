#pragma once
#include "IKeyboardSDK.h"
#include "BaseFeature.h"
#include "RGBLedFeature.h"

class BluetoothFeature : public BaseFeature
{
    private:
        static IKeyboardSDK* keyboardSDK;
        static RGBLedFeature* rgbLedFeature;

        static void noTriggerKeyboardBlink();

    public:
        BluetoothFeature(IKeyboardSDK* keyboardSDK, RGBLedFeature* rgbLedFeature);

        void toggleConnection();
        void triggerReset();
};