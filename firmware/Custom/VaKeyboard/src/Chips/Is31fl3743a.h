#pragma once
#include <Wire.h>
#include <arduino.h>
#include <Adafruit_I2CDevice.h>

#include "Logger/ILogger.h"

class Is31fl3743a
{
private:
	uint8_t i2c_addr = 0;
	TwoWire *wire = NULL;
	Adafruit_I2CDevice *i2c_dev = NULL;
	ILogger *logger = NULL;
	uint8_t enabledColumns = 0;

	uint8_t currentGlobalIntensity = 0;

public:
	Is31fl3743a(uint8_t i2c_addr, TwoWire *wire, ILogger *logger, uint8_t enabledColumns);
	void setLedIntensities(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity);
	void setGlobalIntensity(uint8_t intensity);
	uint8_t getGlobalIntensity();
};
