#include "MacroEvaluator.h"

MacroEvaluator::MacroEvaluator(BaseKeyboardDescriptor* keyboardDescriptor, FeatureScheduller* featureScheduller)
{
    this->keyboardDescriptor = keyboardDescriptor;
    this->featureScheduller = featureScheduller;
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
    
    uint8_t macroCount = this->keyboardDescriptor->getFeatureMacroCount();
    FeatureMacro** featureMacro = this->keyboardDescriptor->getFeatureMacros();
    
    for (uint8_t i = 0; i < macroCount; i++)
    {
        if (featureMacro[i]->activationTime > 0)
        {
            this->featureScheduller->setActivationTime(featureMacro[i]->featureId, featureMacro[i]->activationTime);
        }

        if (featureMacro[i]->duration > 0)
        {
            this->featureScheduller->setActivationTime(featureMacro[i]->featureId, featureMacro[i]->duration);
        }
    }

    delete backup;
}

bool MacroEvaluator::evaluate(Matrix *matrix)
{
    bool wasAnythingTriggered = false;

    auto coordinateMap = this->keyboardDescriptor->getCoordinatesMap();
    FeatureMacro** featureMacro = this->keyboardDescriptor->getFeatureMacros();
    uint8_t macroCount = this->keyboardDescriptor->getFeatureMacroCount();

    for (uint8_t macroIndex=0; macroIndex < macroCount; macroIndex++)
    {
        auto macro = featureMacro[macroIndex];

        bool isAllPressed = macro->keyCodesCount > 0;
        for (uint8_t keyCodeIndex = 0; keyCodeIndex < macro->keyCodesCount; keyCodeIndex++)
        {
            auto keyCode = macro->keyCodes[keyCodeIndex];
            bool isPressed = matrix->getBit(coordinateMap[keyCode]->getRow(), coordinateMap[keyCode]->getColumn());

            isAllPressed &= isPressed;
        }

        if (isAllPressed)
        {
            this->evaluateAllFeatures(macro->featureId, macro->activationTime, macro->duration);

            wasAnythingTriggered = true;
        }
    }

    for (uint8_t i = 0; i < this->featureScheduller->getSchedullerSize(); i++)
    {
        if (this->featureScheduller->isFeatureActive(i))
        {
            auto duration = this->featureScheduller->getFeatureDuration(i);
            this->evaluateAllFeatures(i, 0, duration);
            
            wasAnythingTriggered = true;
        }
    }

    for (uint8_t row = 0; row < matrix->numberOfRows; row++)
    {
        if (matrix->matrixData[row] > 0)
        {
            this->evaluateAllFeatures(BaseFeatures::BaseKeyPress, 0, 0);
        }
    }

    return wasAnythingTriggered;
}

void MacroEvaluator::evaluateAllFeatures(uint8_t featureId, unsigned long activationTime, uint16_t duration)
{
    for (uint8_t i = 0; i < this->registeredFeatureCount; i++)
    {
        this->registeredFeatures[i]->evaluate(featureId, activationTime, duration);
    }
}