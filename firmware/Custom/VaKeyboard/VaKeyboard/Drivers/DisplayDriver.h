#pragma once

#include <arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>

#include <SPI.h>

#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

class DisplayDriver
{
private:
	Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, 7, 6, 8);

public:
	DisplayDriver();
	void initialise();
	void setText(char* text);
};
