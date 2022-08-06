#pragma once

typedef uint8_t KeyCode;

enum KeyType : uint8_t
{
    KEY = 0,
    MEDIA = 1
};

#ifdef FEATHER32U4
#include "HID-APIs/ConsumerAPI.h"
#include "Drivers/Feather32u4/KeyCodes.h"
#endif

#ifdef ARDUINO_MICRO
#include "HID-APIs/ConsumerAPI.h"
#include "Drivers/Micro/KeyCodes.h"
#endif

#ifdef PORTENTA_H7
#include "Drivers/PortentaH7/KeyCodes.h"
#endif
