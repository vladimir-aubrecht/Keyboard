#pragma once

#ifdef FEATHER_ESP32_S3_NOPSRAM

#include <arduino.h>
#include "../IBatteryDriver.h"

class BatteryDriver : public IBatteryDriver
{
public:
    BatteryDriver();

    virtual uint8_t readBatteryLevel();
};

#endif