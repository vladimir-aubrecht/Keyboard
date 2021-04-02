#ifndef _LAYOUT_h
#define _LAYOUT_h

#include "Arduino.h"

class Layout
{
private:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	Layout(uint8_t numberOfRows, uint8_t numberOfColumns);

	uint16_t** getKeymaps();
};

#endif