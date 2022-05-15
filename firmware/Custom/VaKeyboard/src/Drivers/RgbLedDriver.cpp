#include "RgbLedDriver.h"

RgbLedDriver::RgbLedDriver(ILogger *logger)
{
	this->logger = logger;
	this->controller1 = new Is31fl3743a(0x2C, &Wire, logger, 9);
	this->controller2 = new Is31fl3743a(0x23, &Wire, logger, 8);
}

void RgbLedDriver::toggle()
{
	if (this->controller1->getIntensity() > 0)
	{
		this->controller1->setIntensity(0);
	}
	else
	{
		this->controller1->setIntensity(0xff);
	}

	if (this->controller2->getIntensity() > 0)
	{
		this->controller2->setIntensity(0);
	}
	else
	{
		this->controller2->setIntensity(0xff);
	}
}