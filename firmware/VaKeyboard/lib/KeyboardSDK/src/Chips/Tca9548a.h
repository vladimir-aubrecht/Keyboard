#pragma once
#include <Wire.h>
#include <arduino.h>
#include <Adafruit_I2CDevice.h>

#include "Logger/ILogger.h"

class Tca9548a
{
private:
	uint8_t i2c_addr = 0;
	TwoWire *wire = NULL;
	Adafruit_I2CDevice *i2c_dev = NULL;
	ILogger *logger = NULL;

public:
	Tca9548a(uint8_t i2c_addr, TwoWire *wire, ILogger *logger);

	void selectChannel(uint8_t channelId);
};
