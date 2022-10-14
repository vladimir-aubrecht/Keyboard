#pragma once

typedef uint8_t KeyCode;

enum KeyType : uint8_t
{
    KEY = 0,
    MEDIA = 1
};

#ifdef FEATHER32U4
#include "Drivers/Feather32u4/KeyCodes.h"
#endif

#ifdef ARDUINO_MICRO
#include "Drivers/Micro/KeyCodes.h"
#endif

#ifdef PORTENTA_H7
#include "Drivers/PortentaH7/KeyCodes.h"
#endif

#ifdef TINYS3
#include "Drivers/TinyS3/KeyCodes.h"
#endif

#ifdef WROOM32
#include "Drivers/Wroom32/KeyCodes.h"
#endif

#ifdef FEATHER_ESP32_S3_NOPSRAM
#include "Drivers/Feather_ESP32_S3_NOPSRAM/KeyCodes.h"
#endif