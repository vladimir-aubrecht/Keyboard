#pragma once
#include "Matrix/Matrix.h"
#include "BaseKeyboardDescriptor.h"
#include "Features/BaseFeature.h"

class MacroEvaluator
{
    private:
        BaseKeyboardDescriptor* keyboardDescriptor;
        BaseFeature** registeredFeatures = NULL;
        uint8_t registeredFeatureCount = 0;

        void evaluateAllFeatures(uint8_t featureId);

    public:
        struct MacroEvaluatorContext
        {
            public:
                unsigned long LastKeyPressTime;

                MacroEvaluatorContext()
                {
                    LastKeyPressTime = millis();
                }

        };
 
        MacroEvaluator(BaseKeyboardDescriptor* keyboardDescriptor);

        bool evaluate(Matrix *matrix);
        void registerFeature(BaseFeature* feature);

    private:
        MacroEvaluatorContext* context;
};