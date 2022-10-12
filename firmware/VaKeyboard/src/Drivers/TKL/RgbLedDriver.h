#pragma once

#ifdef TKL

#include "../../Chips/Is31fl3743a.h"

class RgbLedDriver
{
private:
	Is31fl3743a *controller1 = NULL;
	Is31fl3743a *controller2 = NULL;
	//ILogger *logger = NULL;
	uint8_t rowsCount = 0;
	uint8_t columnCount = 0;

public:
	RgbLedDriver(ILogger *logger, uint8_t rowsCount, uint8_t columnCount);
	void turnOn();
	void turnOff();
	bool toggle();
	void blink(uint8_t animationPhase, uint8_t x, uint8_t y, uint32_t color);
	void randomizeColors();
	void setColor(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity);
};


#endif