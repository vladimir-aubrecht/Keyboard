#pragma once
#include <Arduino.h>
#include "BaseKeyboardDescriptor.h"

class MatrixDebouncer
{
private:
    uint8_t debounceTimeInMs = 2;
    uint8_t** lastDebounceTimes;

public:
    MatrixDebouncer(BaseKeyboardDescriptor *keymapProvider, uint8_t debounceTimeInMs);

    bool isDebounced(uint8_t row, uint8_t column);
};