#ifdef FEATHER32U4

#include "BatteryDriver.h"

BatteryDriver::BatteryDriver()
{
}

uint8_t BatteryDriver::readBatteryLevel()
{
    /*
    Following code is simplified code below to save some space in final binary:

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage, gives 3.6 - 4.2V

    return (uint8_t)(100 * (measuredvbat - 3.6) / 0.6);
    */

    float measuredvbat = analogRead(9);
    return (uint8_t)(1.07421875 * measuredvbat - 600);
}

#endif