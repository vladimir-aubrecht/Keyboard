#if defined(TKL) && defined(V2)
#include "KeyboardSDK.h"
#include "PinDriver.h"
#include "RgbLedDriver.h"
#include "../../../Chips/Tca9548a.h"
#include "../KeyboardDescriptor.h"

#ifdef FEATHER32U4
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/Feather32u4/BatteryDriver.h"
#include "Drivers/Feather32u4/UsbHidKeyboardDriver.h"
#include "Drivers/Feather32u4/BluetoothKeyboardDriver.h"
#include "Adafruit_BluefruitLE_SPI.h"
#endif

#ifdef TINYS2
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/TinyS2/BatteryDriver.h"
#include "Drivers/TinyS2/UsbHidKeyboardDriver.h"
#include "Drivers/TinyS2/BluetoothKeyboardDriver.h"
#endif

#ifdef PORTENTA_H7
#include "Drivers/SelectiveKeyboardDriver.h"
#include "Drivers/PortentaH7/BatteryDriver.h"
#include "Drivers/PortentaH7/UsbHidKeyboardDriver.h"
#include "Drivers/PortentaH7/BluetoothKeyboardDriver.h"
#endif

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused


KeyboardSDK::KeyboardSDK(uint8_t tca_i2c_addr, uint8_t csPin, uint8_t mosiPin, uint8_t sclkPin, uint8_t misoPin, TwoWire *wire)
{
    this->logger = logger;

    this->logger = NULL;
    this->batteryDriver = new BatteryDriver();
    
    Tca9548a* tca = new Tca9548a(tca_i2c_addr, wire, this->logger);
    this->rgbLedDriver = new RgbLedDriver(logger, this->numberOfRows, this->numberOfColumns, tca);

    IKeyboardDescriptor* keyboardDescriptor = new KeyboardDescriptor(numberOfRows, numberOfColumns);
    
    this->actionEvaluator = new ActionEvaluator(keyboardDescriptor, logger);
    this->primaryKeyboardDriver = new UsbHidKeyboardDriver(keyboardDescriptor);
    
    Adafruit_BluefruitLE_SPI *ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
    IKeyboardDriver* btKeyboardDriver = new BluetoothKeyboardDriver(ble, batteryDriver, keyboardDescriptor, this->logger);
    
    this->activeKeyboardDriver = new SelectiveKeyboardDriver(this->primaryKeyboardDriver, btKeyboardDriver);

    IPinDriver* pinDriver = new PinDriver(new Max7301(csPin, mosiPin, sclkPin, misoPin), logger);

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