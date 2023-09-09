#include "MacroEvaluator.h"

MacroEvaluator::MacroEvaluator(BaseKeyboardDescriptor* keyboardDescriptor)
{
    this->keyboardDescriptor = keyboardDescriptor;
    this->context = new MacroEvaluatorContext();
}

void MacroEvaluator::registerFeature(BaseFeature* feature)
{
    if (registeredFeatures == NULL)
    {
        this->registeredFeatures = new BaseFeature*[1] { feature };
        this->registeredFeatureCount = 1;
        return;
    }

    BaseFeature** backup = this->registeredFeatures;
    
    this->registeredFeatureCount++;
    this->registeredFeatures = new BaseFeature*[this->registeredFeatureCount];

    for (uint8_t i = 0; i < this->registeredFeatureCount - 1; i++)
    {
        this->registeredFeatures[i] = backup[i];
    }

    this->registeredFeatures[this->registeredFeatureCount - 1] = feature;
    
    delete backup;
}

bool MacroEvaluator::evaluate(Matrix *matrix)
{
    for (uint8_t row = 0; row < matrix->numberOfRows; row++)
    {
        if (matrix->matrixData[row] > 0)
        {
            this->context->LastKeyPressTime = millis();
        }
    }

    bool wasAnythingTriggered = false;

    auto coordinateMap = this->keyboardDescriptor->getCoordinatesMap();
    FeatureMacro** featureMacro = this->keyboardDescriptor->getFeatureMacros();
    uint8_t macroCount = this->keyboardDescriptor->getFeatureMacroCount();

    for (uint8_t macroIndex=0; macroIndex < macroCount; macroIndex++)
    {
        auto macro = featureMacro[macroIndex];

        if (macro->keyCodesCount > 0)
        {
            bool isAllPressed = true;
            for (uint8_t keyCodeIndex = 0; keyCodeIndex < macro->keyCodesCount; keyCodeIndex++)
            {
                auto keyCode = macro->keyCodes[keyCodeIndex];
                bool isPressed = matrix->getBit(coordinateMap[keyCode]->getRow(), coordinateMap[keyCode]->getColumn());

                isAllPressed &= isPressed;
            }

            if (isAllPressed)
            {
                delay(80);
                this->evaluateAllFeatures(macro->featureId);

                wasAnythingTriggered = true;
            }
        }
        else
        {
            unsigned long now = millis();

            if (now >= this->context->LastKeyPressTime + macro->activationTimeSinceLastKeyPress)
            {
                this->evaluateAllFeatures(macro->featureId);
            }
            else
            {
                this->evaluateAllFeatures(macro->otherwiseFeatureId);
            }
        }
    }

    return wasAnythingTriggered;
}

void MacroEvaluator::evaluateAllFeatures(uint8_t featureId)
{
    for (uint8_t i = 0; i < this->registeredFeatureCount; i++)
    {
        this->registeredFeatures[i]->evaluate(featureId);
    }
}