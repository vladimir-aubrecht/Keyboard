#ifdef TKL

#include "PinDriver.h"

void PinDriver::refreshCache()
{
	uint32_t banks = 0;
	banks |= ((uint16_t)(~mcp0->readGPIOB())) << 8;
	banks |= ((uint32_t)~mcp1->readGPIOAB()) << 16;
	cache = banks;
}

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	if (pinNumber < 8)
	{
		uint32_t mask = (1 << (7 - pinNumber));
		return (((cache << 16) >> 24) & mask) >> (7 - pinNumber);
	}
	else if (pinNumber < 16)
	{
		uint32_t mask = (1 << (7 - (pinNumber - 8)));
		return ((cache >> 16) & mask) >> (7 - (pinNumber - 8));
	}
	else
	{
		uint32_t mask = (1 << (15 - (pinNumber - 16)));
		return ((cache >> 16) & mask) >> (15 - (pinNumber - 16));
	}
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	mcp0->digitalWrite(pinNumber, value);
}

PinDriver::PinDriver(TwoWire *wire, ILogger *logger)
{
	this->logger = logger;
	uint8_t mcp0Status = mcp0->begin_I2C((uint8_t)MCP23XXX_ADDR, wire);

	if (!mcp0Status)
	{
		// this->logger->logError(F("Failed to initialise first MCP23017."));
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

	uint8_t mcp1Status = mcp1->begin_I2C((uint8_t)MCP23XXX_ADDR + 7, wire); // outside chip next to keyboard edge

	if (!mcp1Status)
	{
		// this->logger->logError(F("Failed to initialise second MCP23017."));
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

#endif