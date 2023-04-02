#pragma once
#include "KeyPressProcessor.h"
#include "Drivers/IRGBLedDriver.h"
#include "Drivers/IBatteryDriver.h"

class IKeyboardSDK
{
    public:
        virtual KeyPressProcessor* GetKeyPressProcessor() = 0;
        virtual IRGBLedDriver* GetRGBLedDriver() = 0;
        virtual IBatteryDriver* GetBatteryDriver() = 0;
        virtual ILogger* GetLogger() = 0;
        virtual IKeyboardDriver* GetPrimaryKeyboardDriver() = 0;
        virtual IKeyboardDriver* GetActiveKeyboardDriver() = 0;
        virtual ActionEvaluator* GetActionEvaluator() = 0;
};