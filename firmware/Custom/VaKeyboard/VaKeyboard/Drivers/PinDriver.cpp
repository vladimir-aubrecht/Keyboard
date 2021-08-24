#include "PinDriver.h"

const byte IODIRA = 0x00;
const byte IODIRB = 0x01;

const byte GPIOA = 0x12; //Register address of port A
const byte GPIOB = 0x13; //Register address of port B

const byte GPPUA = 0x0C; //Pull up register of port A
const byte GPPUB = 0x0D; //Pull up register of port B

uint8_t PinDriver::readPin(uint8_t pinNumber)
{
	//Wire.beginTransmission(0x20);
	//Wire.write((byte)GPIOB); //selects the GPIOB pins
	//Wire.endTransmission();

	//Wire.requestFrom(0x20, 1);
	//byte result = Wire.read(); // store the incoming byte into inputs
	//Serial.println(result);
	//byte mask = 1 << pinNumber;

	//return ~(result & mask);
	if (pinNumber < 8)
	{
		return 1 - mcp0->digitalRead(15 - pinNumber);
	}
	else if (pinNumber < 16)
	{
		return 1 - mcp1->digitalRead(7 - (pinNumber - 8));
	}
	else
	{
		return 1 - mcp1->digitalRead(15 - (pinNumber - 16));
	}
}

void PinDriver::writePin(uint8_t pinNumber, uint8_t value)
{
	uint8_t enabledPinValue = 1 << pinNumber;

	//Wire.beginTransmission(0x20);
	//Wire.write(GPIOB);
	//Wire.write(HIGH); // turns on pins 0 and 1 of GPIOA
	//Wire.endTransmission();

	mcp0->digitalWrite(pinNumber, value);
}

void PinDriver::initialise()
{

	//Wire.begin();
	//Wire.beginTransmission(0x20);
	//Wire.write(IODIRA);
	//Wire.write(0x00); //this sets all port A pins to outputs
	//Wire.endTransmission();

	//Wire.beginTransmission(0x20);
	//Wire.write(IODIRB);
	//Wire.write(0x00); // sets all port B pins to input
	//Wire.endTransmission();

	/*Wire.beginTransmission(0x20);
	Wire.write(GPPUB);
	Wire.write((byte)0xff);
	Wire.endTransmission();*/

	uint8_t mcp0Status = mcp0->begin_I2C((uint8_t)MCP23XXX_ADDR);
	
	if (!mcp0Status) //inside chip, has rows
	{
		Serial.print("Mcp0 status: ");
		Serial.println(mcp0Status);
		while (1);
	}

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp0->pinMode(i, OUTPUT);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp0->pinMode(i, INPUT_PULLUP);
	}

	mcp1->begin_I2C((uint8_t)MCP23XXX_ADDR + 7); //outside chip next to keyboard edge

	for (uint8_t i = 0; i < 8; i++)
	{
		mcp1->pinMode(i, INPUT_PULLUP);
	}

	for (uint8_t i = 8; i < 16; i++)
	{
		mcp1->pinMode(i, INPUT_PULLUP);
	}
}

PinDriver::PinDriver()
{
}