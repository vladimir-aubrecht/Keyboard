#pragma once
#include "../Chips/Is31fl3743a.h"

class RgbLedDriver
{
private:
	Is31fl3743a* controller1 = new Is31fl3743a(0b000, &Wire);
	Is31fl3743a* controller2 = new Is31fl3743a(0b111, &Wire);

public:
	RgbLedDriver();

	void initialise();
};

