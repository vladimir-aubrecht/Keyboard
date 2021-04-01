#ifndef _PinDriver_h
#define _PinDriver_h

#include <Arduino.h>
#include <Adafruit_MCP23017.h>

#include "IPinDriver.h"

class PinDriver : public IPinDriver
{
private:
	Adafruit_MCP23017 mcp0 = Adafruit_MCP23017();
	Adafruit_MCP23017 mcp1 = Adafruit_MCP23017();

public:
	virtual uint8_t readPin(uint8_t pinNumber);
	virtual void writePin(uint8_t pinNumber, uint8_t value);

	PinDriver();

	void initialise();
};

#endif