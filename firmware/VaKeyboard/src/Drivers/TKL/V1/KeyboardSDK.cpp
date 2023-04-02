#if defined(TKL) && defined(V1)
#include "KeyboardSDK.h"
#include "PinDriver.h"
#include "RgbLedDriver.h"
#include "../KeyboardDescriptor.h"

#ifdef FEATHER32U4
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/Feather32u4/BatteryDriver.h"
#include "Drivers/Feather32u4/UsbHidKeyboardDriver.h"
#include "Drivers/Feather32u4/BluetoothKeyboardDriver.h"
#include "Adafruit_BluefruitLE_SPI.h"
#endif

#ifdef ARDUINO_MICRO
#include "Drivers/Micro/BatteryDriver.h"
#include "Drivers/Micro/UsbHidKeyboardDriver.h"
#include "../../../Chips/Max7301.h"
#endif

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused


KeyboardSDK::KeyboardSDK(TwoWire *wire)
{
    this->logger = logger;

    this->logger = NULL;
    this->batteryDriver = new BatteryDriver();
    
    this->rgbLedDriver = new RgbLedDriver(logger, this->numberOfRows, this->numberOfColumns);

    IKeyboardDescriptor* keyboardDescriptor = new KeyboardDescriptor(numberOfRows, numberOfColumns);
    
    this->actionEvaluator = new ActionEvaluator(keyboardDescriptor, logger);
    this->primaryKeyboardDriver = new UsbHidKeyboardDriver(keyboardDescriptor);
    
    #ifdef ARDUINO_MICRO
    this->activeKeyboardDriver = this->primaryKeyboardDriver;
    #else
    Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
    IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(ble, batteryDriver, keyboardDescriptor, this->logger);
    this->activeKeyboardDriver = new SelectiveKeyboardDriver(this->primaryKeyboardDriver, btKeyboardDriver);
    #endif
    
    IPinDriver* pinDriver = new PinDriver(wire, logger);

    this->keypressProcessor = new KeyPressProcessor(
		new MatrixScanner(pinDriver, numberOfRows, numberOfColumns, logger),
		new MatrixEvaluator(new MatrixDebouncer(keyboardDescriptor, 2)),
		this->activeKeyboardDriver,
		keyboardDescriptor,
		this->actionEvaluator,
		this->logger);

}

ActionEvaluator* KeyboardSDK::GetActionEvaluator()
{
    return this->actionEvaluator;
}

KeyPressProcessor* KeyboardSDK::GetKeyPressProcessor()
{
    return this->keypressProcessor;
}

IKeyboardDriver* KeyboardSDK::GetPrimaryKeyboardDriver()
{
    return this->primaryKeyboardDriver;
}

IKeyboardDriver* KeyboardSDK::GetActiveKeyboardDriver()
{
    return this->activeKeyboardDriver;
}

IRGBLedDriver* KeyboardSDK::GetRGBLedDriver()
{
    return this->rgbLedDriver;
}

IBatteryDriver* KeyboardSDK::GetBatteryDriver()
{
    return this->batteryDriver;
}

ILogger* KeyboardSDK::GetLogger()
{
    return this->logger;
}

#endif