#include "BluetoothFeature.h"

BluetoothFeature::BluetoothFeature(IKeyboardSDK* keyboardSDK)
{
    this->keyboardSDK = keyboardSDK;
}

void BluetoothFeature::toggleConnection()
{
    if (this->areFeaturesDisabled())
    {
        return;
    }

    this->blockFeatureProcessing();

	this->keyboardSDK->GetActiveKeyboardDriver()->ResetState();

	if (((SelectiveKeyboardDriver*)keyboardSDK->GetActiveKeyboardDriver())->SwapKeyboards() == keyboardSDK->GetPrimaryKeyboardDriver())
	{
        this->keyboardSDK->GetFeatureScheduller()->setTtlSinceTime(RGBLedFeatures::RGBLedBlinkUSBSelection, millis(), 1000);
	}
	else
	{
        this->keyboardSDK->GetFeatureScheduller()->setTtlSinceTime(RGBLedFeatures::RGBLedBlinkBTSelection, millis(), 1000);
	}
    
    this->keyboardSDK->GetFeatureScheduller()->setActivationTime(RGBLedFeatures::RGBLedResume, millis() + 1000);
}

void BluetoothFeature::triggerReset()
{
    this->keyboardSDK->GetActiveKeyboardDriver()->ResetPairing();
}

void BluetoothFeature::evaluate(uint8_t featureId, unsigned long activationTime, uint16_t duration)
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