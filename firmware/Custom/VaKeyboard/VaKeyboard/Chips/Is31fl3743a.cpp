#include "Is31fl3743a.h"

Is31fl3743a::Is31fl3743a(uint8_t i2c_addr, TwoWire* wire)
{
	this->i2c_addr = i2c_addr;
	this->wire = wire;
}

void Is31fl3743a::initialise()
{
	uint8_t address = (this->i2c_addr << 1) + 0b01000001;

	Serial.print("Address: ");
	Serial.println(address);

	/*this->wire->begin();
	this->wire->beginTransmission(address);
	uint8_t result = this->wire->endTransmission();
	if (result == 0)
	{
		Serial.println("I2C initialised!");
	}
	else
	{
		Serial.println("I2C not initialised!");
		Serial.print(result);
		Serial.println();
	}*/

	this->i2c_dev = new Adafruit_I2CDevice(address, this->wire);
	
	if (!this->i2c_dev->begin())
	{
		Serial.println("I2C not initialised!");
	}
}