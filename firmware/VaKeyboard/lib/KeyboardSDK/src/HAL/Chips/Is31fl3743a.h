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
	uint8_t columnMask = 0;
	uint8_t rowCount = 0;
	uint8_t columnCount = 0;

	uint8_t currentGlobalIntensity = 0;

	// Factors are taking luminosity from datasheet of 19-237-R6GHBHC-A04-2T RGB LED and transforming them to same base. Blue is reference value.
	float redFactor = 2.0;
	float greenFactor = 3.93;
	float blueFactor = 1.0;


public:
	Is31fl3743a(uint8_t i2c_addr, TwoWire *wire, ILogger *logger, uint8_t columnMask, uint8_t rowCount, uint8_t columnCount, uint8_t maxCurrent);
	void setLedIntensities(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity);
	void setGlobalIntensity(uint8_t intensity);
	uint8_t getGlobalIntensity();
};
