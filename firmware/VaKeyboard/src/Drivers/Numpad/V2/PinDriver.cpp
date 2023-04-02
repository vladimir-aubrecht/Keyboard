#if defined(NUMPAD) && defined(V2)

#include "PinDriver.h"

void PinDriver::refreshCache()
{
	uint32_t banks = 0;

	/*
	Ports 19 - 26: 0x53
	*/

	banks |= this->max7301->read(0x53);

	cache = banks >> 4;
}

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	uint32_t mask = (1 << (3 - pinNumber));
	uint8_t result = ((cache & mask) >> (3 - pinNumber));

	return (~result) & 0b00000001;
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	/*
	27: 0x3B
	28: 0x3C
	29: 0x3D
	30: 0x3E
	31: 0x3F
	*/

	this->max7301->write(0x3B + pinNumber, value);
}

PinDriver::PinDriver(Max7301* max7301, ILogger *logger)
{
	this->max7301 = max7301;
	this->max7301->begin();
	this->max7301->enable();

	//00 is forbidden, 01 is output port, 10 is input without pull up, 11 is output with pull up
	this->max7301->write(0x0C,0b11111111); // ports 19 - 16
	this->max7301->write(0x0D,0b11111111); // ports 23 - 20
	this->max7301->write(0x0E,0b01111111); // ports 27 - 24
	this->max7301->write(0x0F,0b01010101); // ports 31 - 28
}

#endif