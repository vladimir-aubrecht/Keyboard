#pragma once
#include "Arduino.h"
#include "KeyCodes.h"

enum BaseFeatures : uint8_t
{
    BaseKeyPress = 12
};

struct FeatureMacro
{
    public:
        uint8_t featureId;
        uint8_t keyCodesCount;
        uint8_t* keyCodes;
        uint16_t duration;
        unsigned long activationTime;

    FeatureMacro(uint8_t featureId, uint8_t keyCodesCount, uint8_t* keyCodes)
    {
        this->featureId = featureId;
        this->keyCodesCount = keyCodesCount;
        this->keyCodes = keyCodes;
        this->duration = 0;
        this->activationTime = 0;
    }

    FeatureMacro(uint8_t featureId, uint16_t duration, unsigned long activationTime)
    {
        this->featureId = featureId;
        this->keyCodesCount = 0;
        this->keyCodes = keyCodes;
        this->duration = duration;
        this->activationTime = activationTime;
    }
};


class BaseFeature
{
    private:
        static bool areFeaturesDisabledFlag;

    protected:
        BaseFeature();

        bool areFeaturesDisabled();
        static void enableFeatureProcessing();  // ActionEvaluator needs to be redesigned to get rid off function pointers to get rid off this static
        void blockFeatureProcessing();

    public:
        virtual void evaluate(uint8_t featureId, unsigned long activationTime, uint16_t duration) = 0;
};