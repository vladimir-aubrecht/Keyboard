#pragma once

#include "Arduino.h"

class FeatureScheduller
{
    private:
            uint16_t* ttlPerFeatureId = NULL;
            unsigned long* activationTimePerFeatureId = NULL;
            uint8_t maxFeatureId = 50; //Max featureId is 50 at this moment

    public:
        FeatureScheduller();
        uint8_t getSchedullerSize();
        bool isFeatureActive(uint8_t featureId);
        uint8_t getFeatureDuration(uint8_t featureId);
        void setActivationTime(uint8_t featureId, unsigned long activationTime);
        void setTtlSinceTime(uint8_t featureId, unsigned long activationTime, uint16_t ttl);
};