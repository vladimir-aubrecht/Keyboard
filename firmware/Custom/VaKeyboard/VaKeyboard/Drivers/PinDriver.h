#ifndef _PinDriver_h
#define _PinDriver_h

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#include "Drivers/IPinDriver.h"

class PinDriver : public IPinDriver
{
private:
	Adafruit_MCP23X17* mcp0 = new Adafruit_MCP23X17();
	Adafruit_MCP23X17* mcp1 = new Adafruit_MCP23X17();

public:
	virtual uint8_t readPin(uint8_t pinNumber);
	virtual void writePin(uint8_t pinNumber, uint8_t value);

	PinDriver();

	void initialise();
};

#endif