#pragma once
#include "KeyPressProcessor.h"
#include "Drivers/IRGBLedDriver.h"
#include "Drivers/IBatteryDriver.h"

#include "Drivers/SelectiveKeyboardDriver.h"

#ifdef ARDUINO_MICRO
#include "Drivers/Micro/config.h"
#include "Drivers/Micro/BatteryDriver.h"
#include "Drivers/Micro/UsbHidKeyboardDriver.h"
#include "Drivers/Micro/BluetoothKeyboardDriver.h"
#endif

#ifdef FEATHER_ESP32_S3_NOPSRAM
#include "Drivers/Feather_ESP32_S3_NOPSRAM/config.h"
#include "Drivers/Feather_ESP32_S3_NOPSRAM/BatteryDriver.h"
#include "Drivers/Feather_ESP32_S3_NOPSRAM/UsbHidKeyboardDriver.h"
#include "Drivers/Feather_ESP32_S3_NOPSRAM/BluetoothKeyboardDriver.h"
#endif

#ifdef FEATHER32U4
#include "Drivers/Feather32u4/config.h"
#include "Drivers/Feather32u4/BatteryDriver.h"
#include "Drivers/Feather32u4/UsbHidKeyboardDriver.h"
#include "Drivers/Feather32u4/BluetoothKeyboardDriver.h"
#include "Adafruit_BluefruitLE_SPI.h"
#endif

#ifdef TINYS2
#include "Drivers/TinyS2/config.h"
#include "Drivers/TinyS2/BatteryDriver.h"
#include "Drivers/TinyS2/UsbHidKeyboardDriver.h"
#include "Drivers/TinyS2/BluetoothKeyboardDriver.h"
#endif

#ifdef PORTENTA_H7
#include "Drivers/PortentaH7/config.h"
#include "Drivers/PortentaH7/BatteryDriver.h"
#include "Drivers/PortentaH7/UsbHidKeyboardDriver.h"
#include "Drivers/PortentaH7/BluetoothKeyboardDriver.h"
#endif

class IKeyboardSDK
{
    protected:
        ILogger *logger = NULL;
        IBatteryDriver* batteryDriver = NULL;
        IKeyboardDriver* primaryKeyboardDriver = NULL;
        IKeyboardDriver* activeKeyboardDriver = NULL;
        IRGBLedDriver* rgbLedDriver = NULL;
        ActionEvaluator* actionEvaluator = NULL;
        KeyPressProcessor* keypressProcessor = NULL;


    public:
        ActionEvaluator* GetActionEvaluator()
        {
            return this->actionEvaluator;
        }

        KeyPressProcessor* GetKeyPressProcessor()
        {
            return this->keypressProcessor;
        }

        IKeyboardDriver* GetPrimaryKeyboardDriver()
        {
            return this->primaryKeyboardDriver;
        }

        IKeyboardDriver* GetActiveKeyboardDriver()
        {
            return this->activeKeyboardDriver;
        }

        IRGBLedDriver* GetRGBLedDriver()
        {
            return this->rgbLedDriver;
        }

        IBatteryDriver* GetBatteryDriver()
        {
            return this->batteryDriver;
        }

        ILogger* GetLogger()
        {
            return this->logger;
        }
};