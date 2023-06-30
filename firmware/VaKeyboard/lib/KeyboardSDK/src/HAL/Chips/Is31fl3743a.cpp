#include "Is31fl3743a.h"
#include <Adafruit_BusIO_Register.h>

Is31fl3743a::Is31fl3743a(uint8_t i2c_addr, TwoWire *wire, ILogger *logger, uint8_t columnMask, uint8_t rowCount, uint8_t columnCount, uint8_t maxCurrent)
{
	this->i2c_addr = i2c_addr;
	this->wire = wire;
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	//this->logger = logger;
	this->columnMask = columnMask;

	this->i2c_dev = new Adafruit_I2CDevice(this->i2c_addr, this->wire);

	this->i2c_dev->begin();

	// if (!this->i2c_dev->begin())
	// {
	// 	//this->logger->logError(F("Failed to initialise IS31FL3743A."));
	// 	return;
	// }

	Adafruit_BusIO_Register CRWL(i2c_dev, 0xFE);
	Adafruit_BusIO_Register CR(i2c_dev, 0xFD);

	this->setGlobalIntensity(0xFF);

	CRWL.write(0xC5); // unlock CR
	CR.write(0x01);	  // lets write scaling
	for (int column = 0; column < columnCount; column++)
	{
		for (int row = 0; row < rowCount * 3; row++)
		{
			uint8_t index = row + (rowCount * 3 * column) + 1; //3 colors in LED
			Adafruit_BusIO_Register SL(i2c_dev, index);
			SL.write(0xFF);
		}
	}

	CRWL.write(0xC5); // unlock CR
	CR.write(0x02);
	Adafruit_BusIO_Register GCC(i2c_dev, 0x01); // global current
	GCC.write(maxCurrent);

	Adafruit_BusIO_Register CONF(i2c_dev, 0x00);
	CONF.write(this->columnMask); // normal mode + enabled columns
return;	
	Adafruit_BusIO_Register PDU(i2c_dev, 0x02);
	PDU.write(0b00110011);

	Adafruit_BusIO_Register TS(i2c_dev, 0x24);
	TS.write(0b00000110);	// temperature control: > 120 C will decrease current to LEDs to 55%.

	Adafruit_BusIO_Register SS(i2c_dev, 0x25);
	SS.write(0b00000001); // configure timing to 1200 us
}

uint8_t Is31fl3743a::getGlobalIntensity()
{
	return this->currentGlobalIntensity;
}

void Is31fl3743a::setGlobalIntensity(uint8_t intensity)
{

	Adafruit_BusIO_Register CRWL(this->i2c_dev, 0xFE);
	Adafruit_BusIO_Register CR(this->i2c_dev, 0xFD);

	CRWL.write(0xC5); // unlock CR
	CR.write(0x00);	  // lets write pwm


	for (int column = 0; column < columnCount; column++)
	{
		for (int row = 0; row < rowCount * 3; row++)
		{
			//uint32_t color = random(0x00ffffff);
			uint8_t r = intensity; //(uint8_t)((color & 0x00ff0000) >> 16);
			uint8_t g = intensity; //(uint8_t)((color & 0x0000ff00) >> 8);
			uint8_t b = intensity; //(uint8_t)(color & 0x000000ff);

			uint8_t index = row + (rowCount * 3 * column) + 1; //3 colors in LED
			Adafruit_BusIO_Register PWM(i2c_dev, index);	

			if ((index - 1) % 3 == 0)	//red led
			{
				PWM.write(2 * r / 5);
			}
			else if ((index - 2) % 3 == 0)	//green led
			{
				PWM.write(g);
			}
			else //blue led
			{
				PWM.write(4 * b / 5);
			}
		}
	}

	this->currentGlobalIntensity = intensity;
}

void Is31fl3743a::setLedIntensities(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity)
{
	return;
	Adafruit_BusIO_Register CRWL(this->i2c_dev, 0xFE);
	Adafruit_BusIO_Register CR(this->i2c_dev, 0xFD);

	CRWL.write(0xC5); // unlock CR
	CR.write(0x00);	  // lets write pwm

	// registers starts at address 0x1
	Adafruit_BusIO_Register rPWM(i2c_dev, y * this->rowCount * 3 + x * 3 + 1);
	Adafruit_BusIO_Register gPWM(i2c_dev, y * this->rowCount * 3 + x * 3 + 2);
	Adafruit_BusIO_Register bPWM(i2c_dev, y * this->rowCount * 3 + x * 3 + 3);
	rPWM.write(redIntensity);
	gPWM.write(greenIntensity);
	bPWM.write(blueIntensity);
}