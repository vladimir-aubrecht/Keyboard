#if defined(TKL) && defined(V2)

#pragma once

#include "Chips/Is31fl3743a.h"
#include "Chips/Tca9548a.h"
#include "HAL/IRGBLedDriver.h"

class RgbLedDriver : public IRGBLedDriver
{
private:
	Is31fl3743a *controller1 = NULL;
	Is31fl3743a *controller2 = NULL;
	Is31fl3743a *controller3 = NULL;
	Is31fl3743a *controller4 = NULL;
	Is31fl3743a *controller5 = NULL;
	Is31fl3743a *controller6 = NULL;
	Is31fl3743a *controller7 = NULL;
	Is31fl3743a *controller8 = NULL;
	Is31fl3743a *controller9 = NULL;
	ILogger *logger = NULL;
	uint8_t rowsCount = 0;
	uint8_t columnCount = 0;

public:
	RgbLedDriver(ILogger *logger, uint8_t rowsCount, uint8_t columnCount, Tca9548a* tca);
	virtual void turnOn();
	virtual void turnOff();
	virtual bool toggle();
	virtual void blink(uint8_t animationPhase, uint8_t x, uint8_t y, uint32_t color);
	virtual void randomizeColors();
	virtual void setColor(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity);
};

#endif