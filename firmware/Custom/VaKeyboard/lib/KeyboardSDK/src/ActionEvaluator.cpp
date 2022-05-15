#include "ActionEvaluator.h"

ActionEvaluator::ActionEvaluator(IKeyMapProvider *keymapProvider, ILogger *logger)
{
    this->logger = logger ?: new NullLogger();
    this->keymapProvider = keymapProvider;
    this->actions = new Action *[0];
}

ActionEvaluator::Action *ActionEvaluator::translateToAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes)
{
    KeyboardKeycode **keymaps = keymapProvider->getKeyMap();

    uint8_t rowCount = keymapProvider->getRowCount();
    uint8_t columnCount = keymapProvider->getColumnCount();

    uint8_t *rows = new uint8_t[keycodesCount];
    uint8_t *columns = new uint8_t[keycodesCount];

    uint8_t currentKeyIndex = 0;
    for (uint8_t row = 0; row < rowCount; row++)
    {
        for (uint8_t column = 0; column < columnCount; column++)
        {
            KeyboardKeycode keyCode = keymaps[row][column];

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

    return new Action(action, keycodesCount, rows, columns);
}

void ActionEvaluator::registerAction(void (*action)(), uint8_t keycodesCount, KeyboardKeycode *keycodes)
{
    uint8_t itemsCount = registeredActionsCount;
    Action **newActions = new Action *[itemsCount + 1];

    for (uint8_t i = 0; i < itemsCount; i++)
    {
        newActions[i] = this->actions[i];
    }

    newActions[itemsCount] = translateToAction(action, keycodesCount, keycodes);

    Action **oldAction = this->actions;
    this->actions = newActions;
    registeredActionsCount++;
    delete oldAction;
}

bool ActionEvaluator::evaluateActions(Matrix *matrix)
{
    for (uint8_t k = 0; k < registeredActionsCount; k++)
    {
        uint8_t allPressed = 1;
        for (uint8_t i = 0; i < this->actions[k]->keycodesCount; i++)
        {
            uint8_t isPressed = (matrix->matrixData[this->actions[k]->rows[i]] >> this->actions[k]->columns[i]) & 1;
            allPressed &= isPressed;
        }

        if (allPressed)
        {
            this->actions[k]->action();
            return true;
        }
    }

    return false;
}