#include "Tca9548a.h"

Tca9548a::Tca9548a(uint8_t i2c_addr, TwoWire *wire, ILogger *logger)
{
   	this->i2c_addr = i2c_addr;
	this->wire = wire;
}

void Tca9548a::selectChannel(uint8_t channelId)
{
    wire->beginTransmission(this->i2c_addr);
    wire->write(1 << channelId);
    wire->endTransmission();
}