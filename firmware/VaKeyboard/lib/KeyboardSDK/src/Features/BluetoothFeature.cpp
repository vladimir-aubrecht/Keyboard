#include "BluetoothFeature.h"

BluetoothFeature::BluetoothFeature(IKeyboardSDK* keyboardSDK)
{
    this->keyboardSDK = keyboardSDK;
}

void BluetoothFeature::toggleConnection()
{
	SelectiveKeyboardDriver* kb = ((SelectiveKeyboardDriver*)this->keyboardSDK->GetActiveKeyboardDriver());
    kb->ResetState();
    kb->SwapKeyboards();
}

void BluetoothFeature::triggerReset()
{
    this->keyboardSDK->GetActiveKeyboardDriver()->ResetPairing();
}

void BluetoothFeature::evaluate(uint8_t featureId)
{
    if (BluetoothKeyboardDriver::GetInstance() != NULL)
    {
        switch (featureId)
        {
        case BluetoothFeatures::BluetoothToggle:
            this->toggleConnection();
            break;
        
        case BluetoothFeatures::BluetoothReset:
            this->triggerReset();
            break;

        default:
            break;
        }
    }
}