#pragma once
#include "../Chips/Is31fl3743a.h"

class RgbLedDriver
{
private:
	Is31fl3743a *controller1 = NULL;
	Is31fl3743a *controller2 = NULL;
	ILogger *logger = NULL;
	void randomizeColorsPerController(Is31fl3743a *controller, uint8_t rowsCount, uint8_t columnCount);

public:
	RgbLedDriver(ILogger *logger);
	void toggle();
	void randomizeColors(uint8_t rowsCount, uint8_t columnCount);
};
