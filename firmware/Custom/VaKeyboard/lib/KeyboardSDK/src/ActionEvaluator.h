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
    void registerMatrixAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes);
    void registerTimerAction(unsigned long millisecondsCount, unsigned long firstRunInMillisecondsCount, void (*triggerAction)(), void (*noTriggerAction)());
    bool evaluateMatrixActions(Matrix *matrix);
    bool evaluateTimerAction();
    void updateTimerActionsTime();

private:
    struct MatrixAction
    {
        uint8_t keycodesCount;
        uint8_t *rows;
        uint8_t *columns;
        void (*action)();

        MatrixAction(void (*action)(), uint8_t keycodesCount, uint8_t *rows, uint8_t *columns)
        {
            this->action = action;
            this->keycodesCount = keycodesCount;
            this->rows = rows;
            this->columns = columns;
        }
    };

    struct TimerAction
    {
        unsigned long lastExecutionTime = 0L;
        unsigned long millisecondsCount = 0L;
        void (*triggerAction)() = NULL;
        void (*noTriggerAction)() = NULL;

        TimerAction(unsigned long millisecondsCount, unsigned long firstRunInMillisecondsCount, void (*triggerAction)(), void (*noTriggerAction)())
        {
            this->lastExecutionTime = firstRunInMillisecondsCount;
            this->millisecondsCount = millisecondsCount;
            this->triggerAction = triggerAction;
            this->noTriggerAction = noTriggerAction;
        }
    };

    uint8_t registeredMatrixActionsCount = 0;
    uint8_t registeredTimerActionsCount = 0;
    ILogger *logger = NULL;
    MatrixAction **matrixActions = NULL;
    TimerAction **timerActions = NULL;
    IKeyMapProvider *keymapProvider = NULL;

    MatrixAction *translateToAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes);
};