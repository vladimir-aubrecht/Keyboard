#include "MatrixDebouncer.h"

MatrixDebouncer::MatrixDebouncer(BaseKeyboardDescriptor *keyboardDescriptor, uint8_t debounceTimeInMs)
{
    this->debounceTimeInMs = debounceTimeInMs;
    uint8_t rowsCount = keyboardDescriptor->getRowCount();
    uint8_t columnCount = keyboardDescriptor->getColumnCount();

    this->lastDebounceTimes = new uint8_t*[rowsCount];

    for (uint8_t row = 0; row < rowsCount; row++)
    {
        this->lastDebounceTimes[row] = new uint8_t[columnCount];

        for (uint8_t column = 0; column < columnCount; column++)
        {
            this->lastDebounceTimes[row][column] = 0;
        }
    }
}

bool MatrixDebouncer::isDebounced(uint8_t row, uint8_t column)
{
    uint8_t currentTime = millis();
    if (this->lastDebounceTimes[row][column] == 0)
    {
        this->lastDebounceTimes[row][column] = currentTime - this->debounceTimeInMs;
        return true;
    }

    if (currentTime - this->lastDebounceTimes[row][column] >= this->debounceTimeInMs)
    {
        this->lastDebounceTimes[row][column] += this->debounceTimeInMs;
        return true;
    }
}