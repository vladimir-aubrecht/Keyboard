#ifdef NUMPAD

#include "PinDriver.h"

void PinDriver::refreshCache()
{
	uint32_t banks = 0;

	//banks = this->max7301->digitalReadRange(18) >> 4; //last 4 bits holds the value

	cache = banks;
}

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	return 0;
	uint32_t mask = (1 << (3 - pinNumber));
	return ((cache & mask) >> (3 - pinNumber));
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	//this->max7301->digitalWrite(pinNumber, value);
}

PinDriver::PinDriver(/*MAX7301* max7301, */ILogger *logger)
{
	return;
	/*
	this->max7301 = max7301;
	this->logger = logger;
	this->max7301->enable();

	for (uint8_t i = 27; i <= 31; i++)
	{
		this->max7301->pinMode(i, GPIO_OUTPUT);
	}

	for (uint8_t i = 23; i <= 25; i++)
	{
		this->max7301->pinMode(i, GPIO_INPUT_PULLUP);
	}*/
}

#endif