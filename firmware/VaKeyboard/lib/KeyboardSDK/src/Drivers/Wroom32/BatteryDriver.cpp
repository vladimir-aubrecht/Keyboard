#ifdef WROOM32
#include "BatteryDriver.h"
BatteryDriver::BatteryDriver()
{
}
uint8_t BatteryDriver::readBatteryLevel()
{
    return 100;
}
#endif