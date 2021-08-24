#pragma once
#include "../Chips/Is31fl3743a.h"

class RgbLedDriver
{
private:
	Is31fl3743a* controller1 = new Is31fl3743a(0b1100, &Wire);
	Is31fl3743a* controller2 = new Is31fl3743a(0b0011, &Wire);

public:
	RgbLedDriver();

	void initialise();
};

