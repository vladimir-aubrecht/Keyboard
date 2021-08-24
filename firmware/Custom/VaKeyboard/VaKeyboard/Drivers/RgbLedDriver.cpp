#include "RgbLedDriver.h"

void RgbLedDriver::initialise()
{
	//this->controller1.initialise();
	this->controller2->initialise();
}

RgbLedDriver::RgbLedDriver()
{
}