#pragma once

#ifdef ARDUINO_MICRO

#include "HAL/MCUs/EmptyBluetoothKeyboardDriver.h"

class BluetoothKeyboardDriver : public EmptyBluetoothKeyboardDriver
{
};

#endif