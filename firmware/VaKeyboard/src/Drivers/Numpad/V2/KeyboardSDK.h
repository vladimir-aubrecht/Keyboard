#if defined(NUMPAD) && defined(V2)
#pragma once

#include "Wire.h"
#include "IKeyboardSDK.h"
#include "Drivers/IRGBLedDriver.h"
#include "Logger/ILogger.h"
#include "KeyPressProcessor.h"

class KeyboardSDK : public IKeyboardSDK
{
    private:
        const uint8_t numberOfRows = 5;
        const uint8_t numberOfColumns = 4;

    public:
        KeyboardSDK(uint8_t csPin, uint8_t mosiPin, uint8_t sclkPin, uint8_t misoPin, TwoWire *wire);
};

#endif