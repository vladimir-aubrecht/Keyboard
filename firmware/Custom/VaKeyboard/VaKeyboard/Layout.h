#ifndef _LAYOUT_h
#define _LAYOUT_h

#include "Arduino.h"

class Layout
{
public:
	Layout();

	uint16_t** getKeymaps();
};

#endif