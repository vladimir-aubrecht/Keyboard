#if defined(TKL) && defined(V1)
#pragma once

#include "Wire.h"
#include "IKeyboardSDK.h"
#include "Drivers/IRGBLedDriver.h"
#include "Logger/ILogger.h"
#include "KeyPressProcessor.h"

class KeyboardSDK : public IKeyboardSDK
{
    private:
        const uint8_t numberOfRows = 6;
        const uint8_t numberOfColumns = 17;

        ILogger *logger = NULL;
        IBatteryDriver* batteryDriver = NULL;
        IKeyboardDriver* primaryKeyboardDriver = NULL;
        IKeyboardDriver* activeKeyboardDriver = NULL;
        IRGBLedDriver* rgbLedDriver = NULL;
        ActionEvaluator* actionEvaluator = NULL;
        KeyPressProcessor* keypressProcessor = NULL;

    public:
        KeyboardSDK(TwoWire *wire);
        virtual KeyPressProcessor* GetKeyPressProcessor();
        virtual IRGBLedDriver* GetRGBLedDriver();
        virtual IBatteryDriver* GetBatteryDriver();
        virtual ILogger* GetLogger();
        virtual IKeyboardDriver* GetPrimaryKeyboardDriver();
        virtual IKeyboardDriver* GetActiveKeyboardDriver();
        virtual ActionEvaluator* GetActionEvaluator();
};

#endif