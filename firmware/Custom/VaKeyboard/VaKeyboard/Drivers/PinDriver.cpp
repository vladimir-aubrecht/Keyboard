#include "PinDriver.h"

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	if (pinNumber < 8)
	{
		return 1 - mcp0->digitalRead(15 - pinNumber);
	}
	else if (pinNumber < 16)
	{
		return 1 - mcp1->digitalRead(7 - (pinNumber - 8));
	}
	else
	{
		return 1 - mcp1->digitalRead(15 - (pinNumber - 16));
	}
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	uint8_t enabledPinValue = 1 << pinNumber;
	mcp0->digitalWrite(pinNumber, value);
}

void PinDriver::initialise()
{
	uint8_t mcp0Status = mcp0->begin_I2C((uint8_t)MCP23XXX_ADDR);
	
	if (!mcp0Status)
	{
		logger->logError("failed to initialise first MCP23017.");
		return;
	}

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp0->pinMode(i, OUTPUT);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp0->pinMode(i, INPUT_PULLUP);
	}

	uint8_t mcp1Status = mcp1->begin_I2C((uint8_t)MCP23XXX_ADDR + 7); //outside chip next to keyboard edge

	if (!mcp1Status)
	{
		logger->logError("failed to initialise second MCP23017.");
		return;
	}

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp1->pinMode(i, INPUT_PULLUP);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp1->pinMode(i, INPUT_PULLUP);
	}
}

PinDriver::PinDriver(ILogger& logger)
{
	this->logger = &logger;
}