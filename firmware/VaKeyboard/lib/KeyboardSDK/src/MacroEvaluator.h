#pragma once
#include "Matrix/Matrix.h"
#include "BaseKeyboardDescriptor.h"
#include "Features/BaseFeature.h"
#include "Features/FeatureScheduller.h"

class MacroEvaluator
{
    private:
        BaseKeyboardDescriptor* keyboardDescriptor;
        BaseFeature** registeredFeatures = NULL;
        FeatureScheduller* featureScheduller = NULL;
        uint8_t registeredFeatureCount;

        void evaluateAllFeatures(uint8_t featureId, unsigned long activationTime, uint16_t duration);

    public:
        MacroEvaluator(BaseKeyboardDescriptor* keyboardDescriptor, FeatureScheduller* featureScheduller);

        bool evaluate(Matrix *matrix);
        void registerFeature(BaseFeature* feature);
};