/*
#include "PinDriver.h"

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	return 1 - mcp0.digitalRead(pinNumber);
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	if (pinNumber < 8)
	{
		mcp0.digitalWrite(15 - pinNumber, value);
	}
	else if (pinNumber < 16)
	{
		mcp1.digitalWrite(7 - (pinNumber - 8), value);
	}
	else
	{
		mcp1.digitalWrite(15 - (pinNumber - 16), value);
	}
}

void PinDriver::initialise()
{
	mcp0.begin((uint8_t)0x20);
	mcp1.begin((uint8_t)0x27);

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp0.pullUp(i, HIGH);
		mcp1.pullUp(i, HIGH);

		mcp0.pinMode(i, INPUT);
		mcp1.pinMode(i, OUTPUT);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp0.pullUp(i, HIGH);
		mcp1.pullUp(i, HIGH);

		mcp0.pinMode(i, OUTPUT);
		mcp1.pinMode(i, OUTPUT);
	}
}

PinDriver::PinDriver()
{
}
*/