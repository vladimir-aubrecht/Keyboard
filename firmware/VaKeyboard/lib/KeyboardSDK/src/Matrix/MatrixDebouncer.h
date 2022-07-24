#pragma once
#include <Arduino.h>
#include "../IKeyMapProvider.h"

class MatrixDebouncer
{
private:
    uint8_t debounceTimeInMs = 2;
    long** lastDebounceTimes;

public:
    MatrixDebouncer(IKeyMapProvider *keymapProvider, uint8_t debounceTimeInMs);

    bool isDebounced(uint8_t row, uint8_t column);
};