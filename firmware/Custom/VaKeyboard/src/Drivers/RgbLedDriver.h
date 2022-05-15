#pragma once
#include "../Chips/Is31fl3743a.h"

class RgbLedDriver
{
private:
	Is31fl3743a *controller1 = NULL;
	Is31fl3743a *controller2 = NULL;
	ILogger *logger = NULL;

public:
	RgbLedDriver(ILogger *logger);
	void toggle();
};
