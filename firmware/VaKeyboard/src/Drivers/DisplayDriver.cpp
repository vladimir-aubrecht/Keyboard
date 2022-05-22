#include "DisplayDriver.h"


DisplayDriver::DisplayDriver(SPIClass* spi)
{
	this->display = new Adafruit_SSD1331(spi, 7, 6, 8);
	display->begin();
	display->fillScreen(BLACK);
	display->setTextSize(1);
	display->setTextColor(WHITE);
	display->setCursor(0, 0);
}

void DisplayDriver::setText(char* text)
{
	display->setCursor(0, 0);
	display->print(text);
}