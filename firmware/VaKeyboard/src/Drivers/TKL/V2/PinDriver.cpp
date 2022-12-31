#ifdef TKL
#ifdef V2

#include "PinDriver.h"

void PinDriver::refreshCache()
{
	uint32_t banks = 0;

	/*
	Columns on TKL
	Ports 15 - 22: 0x4F, last block of columns
	Ports 23 - 30: 0x57, middle block of columns
	Port 31: 0x5F, first column
	*/

	uint32_t firstColumn = this->max7301->read(0x5F);
	uint16_t middleBlock = this->max7301->read(0x57); 
	uint16_t lastBlock = this->max7301->read(0x4F);

	banks |= (firstColumn << 16);
	banks |= (middleBlock << 8);
	banks |= lastBlock;

	cache = banks;
}

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	uint32_t mask = (((uint32_t)1) << (16 - pinNumber));
	uint8_t result = ((cache & mask) >> (16 - pinNumber));

	return (~result) & 0b00000001;
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	/*
	Rows on TKL
	4: 0x24
	5: 0x25
	6: 0x26
	7: 0x27
	8: 0x28
	9: 0x29
	*/

	this->max7301->write(0x29 - pinNumber, value);
}

PinDriver::PinDriver(Max7301* max7301, ILogger *logger)
{
	this->max7301 = max7301;
	this->max7301->begin();

	this->max7301->write(0x06, 0xff);

	//00 is forbidden, 01 is output port, 10 is input without pull up, 11 is output with pull up

	this->max7301->write(0x09, 0b01010101); // ports 7 - 4, rows
	this->max7301->write(0x0A, 0b01010101); // ports 11 - 8, rows
	
	this->max7301->write(0x0B, 0b11111111); // ports 15 - 12, columns
	this->max7301->write(0x0C, 0b11111111); // ports 19 - 16, columns
	this->max7301->write(0x0D, 0b11111111); // ports 23 - 20, columns
	this->max7301->write(0x0E, 0b11111111); // ports 27 - 24, columns
	this->max7301->write(0x0F, 0b11111111); // ports 31 - 28, columns

	this->max7301->enable();
}

#endif
#endif