#pragma once
#include "Arduino.h"
#include "KeyCodes.h"

enum BaseFeatures : uint8_t
{
};

struct FeatureMacro
{
    public:
        uint8_t featureId;
        uint8_t otherwiseFeatureId;
        uint8_t keyCodesCount;
        uint8_t* keyCodes;
        long activationTimeSinceLastKeyPress;

    FeatureMacro(uint8_t featureId, uint8_t keyCodesCount, uint8_t* keyCodes)
    {
        this->featureId = featureId;
        this->otherwiseFeatureId = featureId;
        this->keyCodesCount = keyCodesCount;
        this->keyCodes = keyCodes;
        this->activationTimeSinceLastKeyPress = 0;
    }

    FeatureMacro(uint8_t featureId, uint8_t otherwiseFeatureId, long activationTimeSinceLastKeyPress)
    {
        this->featureId = featureId;
        this->otherwiseFeatureId = otherwiseFeatureId;
        this->keyCodesCount = 0;
        this->keyCodes = keyCodes;
        this->activationTimeSinceLastKeyPress = activationTimeSinceLastKeyPress;
    }
};


class BaseFeature
{
    private:

    protected:
        BaseFeature();

    public:
        virtual void evaluate(uint8_t featureId) = 0;
};