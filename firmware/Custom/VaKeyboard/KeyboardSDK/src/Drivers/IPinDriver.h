#ifndef _IPinDriver_h
#define _IPinDriver_h

#include <arduino.h>

class IPinDriver
{
public:
	virtual uint8_t readPin(uint8_t pinNumber) = 0;
	virtual void writePin(uint8_t pinNumber, uint8_t value) = 0;
};

#endif

