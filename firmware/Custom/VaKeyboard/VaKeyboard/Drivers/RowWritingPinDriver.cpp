#include "PinDriver.h"

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	if (pinNumber < 8)
	{
		return 1 - mcp0.digitalRead(15 - pinNumber);
	}
	else if (pinNumber < 16)
	{
		return 1 - mcp1.digitalRead(7 - (pinNumber - 8));
	}
	else
	{
		return 1 - mcp1.digitalRead(15 - (pinNumber - 16));
	}
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	mcp0.digitalWrite(pinNumber, value);
}

void PinDriver::initialise()
{
	mcp0.begin((uint8_t)0x20); //inside chip, has rows
	mcp1.begin((uint8_t)0x27); //outside chip next to keyboard edge

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp0.pullUp(i, HIGH);
		mcp1.pullUp(i, HIGH);
		
		mcp0.pinMode(i, OUTPUT);
		mcp1.pinMode(i, INPUT);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp0.pullUp(i, HIGH);
		mcp1.pullUp(i, HIGH);

		mcp0.pinMode(i, INPUT);
		mcp1.pinMode(i, INPUT);
	}
}

PinDriver::PinDriver()
{
}