#pragma once

#ifdef TKL
#ifdef V2

#include <Arduino.h>
#include "../../../Chips/Max7301.h"

#include "Drivers/IPinDriver.h"
#include "Logger/ILogger.h"

class PinDriver : public IPinDriver
{
private:
	Max7301* max7301;
	ILogger *logger = NULL;
	uint32_t cache = 0;

public:
	virtual uint8_t readPin(uint8_t pinNumber);
	virtual void writePin(uint8_t pinNumber, uint8_t value);
	virtual void refreshCache();

	PinDriver(Max7301* max7301, ILogger *logger);
};

#endif
#endif