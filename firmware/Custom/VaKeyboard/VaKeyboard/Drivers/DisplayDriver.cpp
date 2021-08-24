#include "DisplayDriver.h"


DisplayDriver::DisplayDriver()
{

}

void DisplayDriver::initialise()
{
	display.begin();
	display.fillScreen(BLACK);
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
}

void DisplayDriver::setText(char* text)
{
	display.setCursor(0, 0);
	display.print(text);
}