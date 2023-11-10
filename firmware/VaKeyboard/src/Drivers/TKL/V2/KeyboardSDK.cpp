#if defined(TKL) && defined(V2)
#include "KeyboardSDK.h"
#include "HAL/Chips/Tca9548a.h"
#include "../KeyboardDescriptor.h"
#include "PinDriver.h"
#include "RgbLedDriver.h"

KeyboardSDK::KeyboardSDK(uint8_t csPin, uint8_t mosiPin, uint8_t sclkPin, uint8_t misoPin, TwoWire *wire, ILogger* logger)
{
    this->logger = logger;
    this->batteryDriver = new BatteryDriver();
    
    Tca9548a* tca = new Tca9548a(0x70, wire, this->logger);
    this->rgbLedDriver = new RgbLedDriver(logger, this->numberOfRows, this->numberOfColumns, tca);

    BaseKeyboardDescriptor* keyboardDescriptor = new KeyboardDescriptor(numberOfRows, numberOfColumns);
    this->macroEvaluator = new MacroEvaluator(keyboardDescriptor);
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
        this->macroEvaluator,
		this->logger);
}

#endif