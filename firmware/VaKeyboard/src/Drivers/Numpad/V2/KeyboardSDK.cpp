#if defined(NUMPAD) && defined(V2)
#include "KeyboardSDK.h"
#include "PinDriver.h"
#include "RgbLedDriver.h"
#include "HAL/Chips/Tca9548a.h"
#include "../KeyboardDescriptor.h"

KeyboardSDK::KeyboardSDK(uint8_t csPin, uint8_t mosiPin, uint8_t sclkPin, uint8_t misoPin, TwoWire *wire)
{
    this->logger = logger;

    this->logger = NULL;
    this->batteryDriver = new BatteryDriver();
    this->rgbLedDriver = new RgbLedDriver(logger, numberOfRows, numberOfColumns);
    
    BaseKeyboardDescriptor* keyboardDescriptor = new KeyboardDescriptor(numberOfRows, numberOfColumns);
    
    this->actionEvaluator = new ActionEvaluator(keyboardDescriptor, logger);
    this->primaryKeyboardDriver = new UsbHidKeyboardDriver(keyboardDescriptor);
    this->activeKeyboardDriver = this->primaryKeyboardDriver;

    IKeyboardDriver* btKeyboardDriver = BluetoothKeyboardDriver::Create(batteryDriver, keyboardDescriptor, this->logger);

    if (btKeyboardDriver != NULL)
    {
        this->activeKeyboardDriver = new SelectiveKeyboardDriver(this->activeKeyboardDriver, btKeyboardDriver);
    }

    IPinDriver* pinDriver = new PinDriver(new Max7301(csPin, mosiPin, sclkPin, misoPin), logger);

    this->keypressProcessor = new KeyPressProcessor(
		new MatrixScanner(pinDriver, numberOfRows, numberOfColumns, logger),
		new MatrixEvaluator(new MatrixDebouncer(keyboardDescriptor, 2)),
		this->activeKeyboardDriver,
		keyboardDescriptor,
		this->actionEvaluator,
		this->logger);
}

#endif