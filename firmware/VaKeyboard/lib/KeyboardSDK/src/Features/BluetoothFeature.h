#pragma once
#include "IKeyboardSDK.h"
#include "BaseFeature.h"
#include "RGBLedFeature.h"

enum BluetoothFeatures : uint8_t
{
    BluetoothToggle = 1,
    BluetoothReset = 2
};

class BluetoothFeature : public BaseFeature
{
    private:
        IKeyboardSDK* keyboardSDK = NULL;

        void toggleConnection();
        void triggerReset();

    public:
        BluetoothFeature(IKeyboardSDK* keyboardSDK);

        virtual void evaluate(uint8_t featureId, unsigned long activationTime, uint16_t duration);
};