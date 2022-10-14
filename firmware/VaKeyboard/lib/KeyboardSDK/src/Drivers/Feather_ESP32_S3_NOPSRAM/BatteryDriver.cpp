#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "BatteryDriver.h"

BatteryDriver::BatteryDriver()
{
}

uint8_t BatteryDriver::readBatteryLevel()
{
    return 100;
}

#endif