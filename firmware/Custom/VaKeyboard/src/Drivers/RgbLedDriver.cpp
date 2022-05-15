#include "RgbLedDriver.h"

RgbLedDriver::RgbLedDriver(ILogger *logger)
{
	this->logger = logger;
	this->controller1 = new Is31fl3743a(0x2C, &Wire, logger, 9);
	this->controller2 = new Is31fl3743a(0x23, &Wire, logger, 8);
}

void RgbLedDriver::randomizeColors(uint8_t rowsCount, uint8_t columnCount)
{
	this->randomizeColorsPerController(this->controller1, rowsCount, columnCount);
	this->randomizeColorsPerController(this->controller2, rowsCount, columnCount);
}

void RgbLedDriver::randomizeColorsPerController(Is31fl3743a *controller, uint8_t rowsCount, uint8_t columnCount)
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

	for (uint8_t row = 0; row < rowsCount; row++)
	{
		for (uint8_t column = 0; column < columnCount; column++)
		{
			r = random(0xff);
			g = random(0xff);
			b = random(0xff);
			controller->setLedIntensities(row, column, r, g, b);
		}
	}
}

void RgbLedDriver::toggle()
{
	if (this->controller1->getGlobalIntensity() > 0)
	{
		this->controller1->setGlobalIntensity(0);
	}
	else
	{
		this->controller1->setGlobalIntensity(0xff);
	}

	if (this->controller2->getGlobalIntensity() > 0)
	{
		this->controller2->setGlobalIntensity(0);
	}
	else
	{
		this->controller2->setGlobalIntensity(0xff);
	}
}