#pragma once

#include <Arduino.h>
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"
#include "Matrix/Matrix.h"
#include "KeyCodes.h"
#include "IKeyMapProvider.h"

class ActionEvaluator
{
public:
    ActionEvaluator(IKeyMapProvider *keymapProvider, ILogger *logger);
    void registerAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes);
    bool evaluateActions(Matrix *matrix);

private:
    struct Action
    {
        uint8_t keycodesCount;
        uint8_t *rows;
        uint8_t *columns;
        void (*action)();

        Action(void (*action)(), uint8_t keycodesCount, uint8_t *rows, uint8_t *columns)
        {
            this->action = action;
            this->keycodesCount = keycodesCount;
            this->rows = rows;
            this->columns = columns;
        }
    };

    uint8_t registeredActionsCount = 0;
    ILogger *logger;
    Action **actions;
    IKeyMapProvider *keymapProvider;

    Action *translateToAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes);
};