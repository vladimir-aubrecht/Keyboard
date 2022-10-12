#ifdef ARDUINO_MICRO

#include "BatteryDriver.h"

BatteryDriver::BatteryDriver()
{
}

uint8_t BatteryDriver::readBatteryLevel()
{
    return 100;
}

#endif