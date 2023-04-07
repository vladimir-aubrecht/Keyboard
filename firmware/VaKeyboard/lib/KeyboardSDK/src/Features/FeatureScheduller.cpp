#include "FeatureScheduller.h"

FeatureScheduller::FeatureScheduller()
{
    this->ttlPerFeatureId = new uint16_t[this->maxFeatureId];  
    this->activationTimePerFeatureId = new unsigned long[this->maxFeatureId];
}


uint8_t FeatureScheduller::getSchedullerSize()
{
    return this->maxFeatureId;
}

uint8_t FeatureScheduller::getFeatureDuration(uint8_t featureId)
{
    return this->ttlPerFeatureId[featureId];
}

bool FeatureScheduller::isFeatureActive(uint8_t featureId)
{
    unsigned long now = millis();

    return now >= this->activationTimePerFeatureId[featureId] && (now - this->activationTimePerFeatureId[featureId] <= this->ttlPerFeatureId[featureId]);
}

void FeatureScheduller::setActivationTime(uint8_t featureId, unsigned long activationTime)
{
    this->ttlPerFeatureId[featureId] = 100;
    this->activationTimePerFeatureId[featureId] = activationTime;
}

void FeatureScheduller::setTtlSinceTime(uint8_t featureId, unsigned long activationTime, uint16_t ttl)
{
    this->ttlPerFeatureId[featureId] = ttl;
    this->activationTimePerFeatureId[featureId] = activationTime;
}