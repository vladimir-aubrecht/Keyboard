#include "MatrixDebouncer.h"

MatrixDebouncer::MatrixDebouncer(IKeyMapProvider *keymapProvider, uint8_t debounceTimeInMs)
{
    this->debounceTimeInMs = debounceTimeInMs;
    uint8_t rowsCount = keymapProvider->getRowCount();
    uint8_t columnCount = keymapProvider->getColumnCount();

    this->lastDebounceTimes = new long*[rowsCount];

    for (uint8_t row = 0; row < rowsCount; row++)
    {
        this->lastDebounceTimes[row] = new long[columnCount];

        for (uint8_t column = 0; column < columnCount; column++)
        {
            this->lastDebounceTimes[row][column] = -1;
        }
    }
}

bool MatrixDebouncer::isDebounced(uint8_t row, uint8_t column)
{
    if (this->lastDebounceTimes[row][column] == -1)
    {
        this->lastDebounceTimes[row][column] = millis();
        return true;
    }

    long currentTime = millis();
    if (currentTime - this->lastDebounceTimes[row][column] >= this->debounceTimeInMs)
    {
        this->lastDebounceTimes[row][column] = millis();
        return true;
    }
}