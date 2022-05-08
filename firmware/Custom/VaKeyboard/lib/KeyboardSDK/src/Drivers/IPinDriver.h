#pragma once
#include <arduino.h>

class IPinDriver
{
public:
	virtual uint8_t readPin(uint8_t pinNumber) = 0;
	virtual void writePin(uint8_t pinNumber, uint8_t value) = 0;
	virtual void refreshCache() = 0;
};