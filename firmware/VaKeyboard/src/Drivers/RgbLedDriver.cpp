#include "RgbLedDriver.h"

RgbLedDriver::RgbLedDriver(ILogger *logger, uint8_t rowsCount, uint8_t columnCount)
{
	this->logger = logger;
	this->rowsCount = rowsCount;
	this->columnCount = columnCount;
	this->controller1 = new Is31fl3743a(0x2C, &Wire, logger, 9);
	this->controller2 = new Is31fl3743a(0x23, &Wire, logger, 8);
}

void RgbLedDriver::blink(uint8_t animationPhase, uint8_t x, uint8_t y, uint32_t color)
{
	uint8_t r = (uint8_t)((color & 0x00ff0000) >> 16);
	uint8_t g = (uint8_t)((color & 0x0000ff00) >> 8);
	uint8_t b = (uint8_t)(color & 0x000000ff);
	uint8_t intensity = (256 - animationPhase);

	this->setColor(x, y, r / intensity, g / intensity, b / intensity);
}

void RgbLedDriver::setColor(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity)
{
	if (y < 9)
	{
		controller1->setLedIntensities(x, y, redIntensity, greenIntensity, blueIntensity);
	}
	else
	{
		controller2->setLedIntensities(x, y - 9, redIntensity, greenIntensity, blueIntensity);
	}
}

void RgbLedDriver::randomizeColors()
{
	for (uint8_t row = 0; row < this->rowsCount; row++)
	{
		for (uint8_t column = 0; column < this->columnCount; column++)
		{
			uint32_t color = random(0x00ffffff);
			uint8_t r = (uint8_t)((color & 0x00ff0000) >> 16);
			uint8_t g = (uint8_t)((color & 0x0000ff00) >> 8);
			uint8_t b = (uint8_t)(color & 0x000000ff);

			this->setColor(row, column, r, g, b);
		}
	}
}

void RgbLedDriver::turnOn()
{
	if (this->controller1->getGlobalIntensity() == 0)
	{
		this->controller1->setGlobalIntensity(0xff);
	}

	if (this->controller2->getGlobalIntensity() == 0)
	{
		this->controller2->setGlobalIntensity(0xff);
	}
}

void RgbLedDriver::turnOff()
{
	this->controller1->setGlobalIntensity(0);
	this->controller2->setGlobalIntensity(0);
}

bool RgbLedDriver::toggle()
{
	if (this->controller1->getGlobalIntensity() > 0)
	{
		turnOff();
		return false;
	}
	else
	{
		turnOn();
		return true;
	}
}