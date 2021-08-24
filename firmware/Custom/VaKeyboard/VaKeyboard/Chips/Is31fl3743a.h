#pragma once
#include <Wire.h>
#include <arduino.h>
#include <Adafruit_I2CDevice.h>

class Is31fl3743a
{
private:
	uint8_t i2c_addr = 0;
	TwoWire* wire = NULL;
	Adafruit_I2CDevice* i2c_dev = NULL;

public:
	Is31fl3743a(uint8_t i2c_addr, TwoWire* wire);

	void initialise();
};

