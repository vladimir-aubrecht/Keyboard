#pragma once

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "Drivers/IPinDriver.h"
#include "ILogger.h"

class PinDriver : public IPinDriver
{
private:
	Adafruit_MCP23X17* mcp0 = new Adafruit_MCP23X17();
	Adafruit_MCP23X17* mcp1 = new Adafruit_MCP23X17();
	ILogger* logger = NULL;

public:
	virtual uint8_t readPin(uint8_t pinNumber);
	virtual void writePin(uint8_t pinNumber, uint8_t value);

	PinDriver(ILogger* logger);
};