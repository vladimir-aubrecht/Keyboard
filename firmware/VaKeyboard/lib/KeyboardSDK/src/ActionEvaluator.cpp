#include "ActionEvaluator.h"

ActionEvaluator::ActionEvaluator(IKeyboardDescriptor *keyboardDescriptor, ILogger *logger)
{
    //this->logger = logger;
    this->matrixActions = new MatrixAction *[0];
    this->keyboardDescriptor = keyboardDescriptor;
}

ActionEvaluator::MatrixAction *ActionEvaluator::translateToAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes)
{
    uint8_t *rows = new uint8_t[keycodesCount];
    uint8_t *columns = new uint8_t[keycodesCount];

    uint8_t currentKeyIndex = 0;
    
    for (uint8_t row = 0; row < this->keyboardDescriptor->getRowCount(); row++)
    {
        for (uint8_t column = 0; column < this->keyboardDescriptor->getColumnCount(); column++)
        {
            KeyboardKeycode keyCode = this->keyboardDescriptor->getKeyMap()[0][row][column];

            for (uint8_t keycodeIndex = 0; keycodeIndex < keycodesCount; keycodeIndex++)
            {
                if (keyCode == keycodes[keycodeIndex])
                {
                    rows[currentKeyIndex] = row;
                    columns[currentKeyIndex] = column;
                    currentKeyIndex++;
                }
            }
        }
    }

    return new MatrixAction(action, keycodesCount, rows, columns);
}

void ActionEvaluator::registerMatrixAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes)
{
    uint8_t itemsCount = registeredMatrixActionsCount;
    MatrixAction **newActions = new MatrixAction *[itemsCount + 1];

    for (uint8_t i = 0; i < itemsCount; i++)
    {
        newActions[i] = this->matrixActions[i];
    }

    newActions[itemsCount] = translateToAction(action, keycodesCount, keycodes);

    MatrixAction **oldAction = this->matrixActions;
    this->matrixActions = newActions;
    registeredMatrixActionsCount++;

    if (oldAction != NULL)
    {
        delete oldAction;
    }
}

bool ActionEvaluator::evaluateMatrixActions(Matrix *matrix)
{
    for (uint8_t k = 0; k < registeredMatrixActionsCount; k++)
    {
        uint8_t allPressed = 1;
        for (uint8_t i = 0; i < this->matrixActions[k]->keycodesCount; i++)
        {
            uint8_t isPressed = (matrix->matrixData[this->matrixActions[k]->rows[i]] >> this->matrixActions[k]->columns[i]) & 1;
            allPressed &= isPressed;
        }

        if (allPressed)
        {
            this->matrixActions[k]->action();
            return true;
        }
    }

    return false;
}

void ActionEvaluator::registerTemporaryTimerAction(unsigned long millisecondsCount, void (*triggerAction)(), void (*noTriggerAction)())
{
    this->temporaryTimerActions = new TimerAction(millisecondsCount, millis(), triggerAction, noTriggerAction);
}

void ActionEvaluator::registerTimerAction(unsigned long millisecondsCount, unsigned long firstRunInMillisecondsCount, void (*triggerAction)(), void (*noTriggerAction)())
{
    uint8_t itemsCount = registeredTimerActionsCount;
    TimerAction **newActions = new TimerAction *[itemsCount + 1];

    for (uint8_t i = 0; i < itemsCount; i++)
    {
        newActions[i] = this->timerActions[i];
    }

    newActions[itemsCount] = new TimerAction(millisecondsCount, firstRunInMillisecondsCount, triggerAction, noTriggerAction);

    TimerAction **oldAction = this->timerActions;
    this->timerActions = newActions;
    registeredTimerActionsCount++;

    if (oldAction != NULL)
    {
        delete oldAction;
    }
}

bool ActionEvaluator::evaluateTimerAction()
{
    unsigned long currentTime = millis();

    if (this->temporaryTimerActions != NULL)
    {
        this->temporaryTimerActions->triggerAction();

        if ((unsigned long)(currentTime - this->temporaryTimerActions->lastExecutionTime) > this->temporaryTimerActions->millisecondsCount)
        {
            this->temporaryTimerActions->noTriggerAction();
            delete this->temporaryTimerActions;
            this->temporaryTimerActions = NULL;
        }

        return false;
    }

    for (uint8_t k = 0; k < registeredTimerActionsCount; k++)
    {
        TimerAction *action = this->timerActions[k];

        if ((unsigned long)(currentTime - action->lastExecutionTime) > action->millisecondsCount)
        {
            action->triggerAction();
        }
        else
        {
            action->noTriggerAction();
        }
    }

    return false;
}

void ActionEvaluator::updateTimerActionsTime()
{
    for (uint8_t k = 0; k < registeredTimerActionsCount; k++)
    {
        TimerAction *action = this->timerActions[k];
        action->lastExecutionTime = millis();
    }
}