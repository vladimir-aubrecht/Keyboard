#include "BaseFeature.h"

bool BaseFeature::areFeaturesDisabledFlag = false;

BaseFeature::BaseFeature()
{
    
}

bool BaseFeature::areFeaturesDisabled()
{
    return this->areFeaturesDisabledFlag;
}

void BaseFeature::enableFeatureProcessing()
{
    areFeaturesDisabledFlag = false;
}

void BaseFeature::blockFeatureProcessing()
{
    this->areFeaturesDisabledFlag = true;
}