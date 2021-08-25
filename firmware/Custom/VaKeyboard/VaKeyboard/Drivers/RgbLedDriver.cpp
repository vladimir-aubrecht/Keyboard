#include "RgbLedDriver.h"

void RgbLedDriver::initialise()
{
	this->controller1->initialise();
	this->controller2->initialise();
}

RgbLedDriver::RgbLedDriver(ILogger& logger)
{
	this->logger = &logger;
	this->controller1 = new Is31fl3743a(0x2C, &Wire, logger, 9);
	this->controller2 = new Is31fl3743a(0x23, &Wire, logger, 8);
}