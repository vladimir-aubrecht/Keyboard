#include "PinDriver.h"

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	if (pinNumber < 16)
	{
		return 1 - mcp0.digitalRead(pinNumber);
	}
	else
	{
		return 1 - mcp1.digitalRead(pinNumber - 16);
	}
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	mcp1.digitalWrite(8 + pinNumber, value);
}

void PinDriver::initialise()
{
	mcp0.begin((uint8_t)0x0);
	mcp1.begin((uint8_t)0xff);

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp0.pullUp(i, HIGH);
		mcp1.pullUp(i, HIGH);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp0.pullUp(i, HIGH);
		mcp1.pullUp(i, HIGH);

		mcp1.pinMode(i, OUTPUT);
	}
}

PinDriver::PinDriver()
{
}