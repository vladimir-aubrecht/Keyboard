#if defined(TKL) && defined(V2)

#include "RgbLedDriver.h"

RgbLedDriver::RgbLedDriver(ILogger *logger, uint8_t rowsCount, uint8_t columnCount, Tca9548a* tca)
{
	this->logger = logger;
	this->rowsCount = rowsCount;
	this->columnCount = columnCount;
	this->tca = tca;

	tca->selectChannel(0);

	uint8_t maxCurrent = 0x2F;
	this->controllers = new Is31fl3743a*[this->controllersCount];
	this->controllers[0] = new Is31fl3743a(0x20, &Wire, logger, 0b10011001, 6, 2, maxCurrent);
	this->controllers[1] = new Is31fl3743a(0x23, &Wire, logger, 0b10011001, 6, 2, maxCurrent);
	this->controllers[2] = new Is31fl3743a(0x2C, &Wire, logger, 0b10011001, 6, 2, maxCurrent);
	this->controllers[3] = new Is31fl3743a(0x2F, &Wire, logger, 0b10011001, 6, 2, maxCurrent);

	tca->selectChannel(1);

	this->controllers[4] = new Is31fl3743a(0x20, &Wire, logger, 0b10011001, 6, 2, maxCurrent);
	this->controllers[5] = new Is31fl3743a(0x23, &Wire, logger, 0b10011001, 6, 2, maxCurrent);
	this->controllers[6] = new Is31fl3743a(0x2C, &Wire, logger, 0b10011001, 6, 2, maxCurrent);
	this->controllers[7] = new Is31fl3743a(0x2F, &Wire, logger, 0b10011001, 6, 2, maxCurrent);

	tca->selectChannel(2);
	this->controllers[8] = new Is31fl3743a(0x20, &Wire, logger, 0b10101001, 6, 1, maxCurrent);

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
	uint8_t index = y / 2;
	this->tca->selectChannel(index / 4);
	this->controllers[index]->setLedIntensities(x, y % 2, redIntensity, greenIntensity, blueIntensity);
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
	for (uint8_t i = 0; i < this->controllersCount; i++)
	{
		this->tca->selectChannel(i / 4);
		if (this->controllers[i]->getGlobalIntensity() == 0)
		{
			this->controllers[i]->setGlobalIntensity(0xff);
		}
	}
}

void RgbLedDriver::turnOff()
{
	for (uint8_t i = 0; i < this->controllersCount; i++)
	{
		this->tca->selectChannel(i / 4);
		this->controllers[i]->setGlobalIntensity(0);
	}
}

bool RgbLedDriver::toggle()
{
	if (this->controllers[0]->getGlobalIntensity() > 0)
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

#endif