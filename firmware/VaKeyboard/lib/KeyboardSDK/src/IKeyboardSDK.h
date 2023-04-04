#pragma once
#include "KeyPressProcessor.h"
#include "HAL/IRGBLedDriver.h"
#include "HAL/IBatteryDriver.h"

#include "HAL/SelectiveKeyboardDriver.h"
#include "HAL/MCU.h"

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