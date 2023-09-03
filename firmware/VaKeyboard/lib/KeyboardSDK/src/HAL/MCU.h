#pragma once

#ifdef ARDUINO_MICRO
#include "HAL/MCUs/Micro/config.h"
#include "HAL/MCUs/Micro/UsbHidKeyboardDriver.h"
#include "HAL/MCUs/FullBatteryDriver.h"
#include "HAL/MCUs/EmptyBluetoothKeyboardDriver.h"
#endif

#ifdef FEATHER_ESP32_S3_NOPSRAM
#include "HAL/MCUs/Feather_ESP32_S3_NOPSRAM/config.h"
#include "HAL/MCUs/Feather_ESP32_S3_NOPSRAM/UsbHidKeyboardDriver.h"
#include "HAL/MCUs/Feather_ESP32_S3_NOPSRAM/BluetoothKeyboardDriver.h"
#include "HAL/MCUs/FullBatteryDriver.h"
#endif

#ifdef FEATHER32U4
#include "HAL/MCUs/Feather32u4/config.h"
#include "HAL/MCUs/Feather32u4/BatteryDriver.h"
#include "HAL/MCUs/Feather32u4/UsbHidKeyboardDriver.h"
#include "HAL/MCUs/Feather32u4/BluetoothKeyboardDriver.h"
#endif

#ifdef TINYS2
#include "HAL/MCUs/TinyS2/config.h"
#include "HAL/MCUs/TinyS2/UsbHidKeyboardDriver.h"
#include "HAL/MCUs/EmptyBluetoothKeyboardDriver.h"
#include "HAL/MCUs/FullBatteryDriver.h"
#endif

#ifdef TINYS3
#include "HAL/MCUs/TinyS3/config.h"
#include "HAL/MCUs/TinyS3/UsbHidKeyboardDriver.h"
#include "HAL/MCUs/EmptyBluetoothKeyboardDriver.h"
#include "HAL/MCUs/FullBatteryDriver.h"
#endif

#ifdef PORTENTA_H7
#include "HAL/MCUs/PortentaH7/config.h"
#include "HAL/MCUs/PortentaH7/UsbHidKeyboardDriver.h"
#include "HAL/MCUs/PortentaH7/BluetoothKeyboardDriver.h"
#include "HAL/MCUs/FullBatteryDriver.h"
#endif