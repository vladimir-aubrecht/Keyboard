#ifndef _LAYOUT_h
#define _LAYOUT_h

#include "Arduino.h"
#include "IKeyMapProvider.h"

class KeyMapProvider : public IKeyMapProvider
{
private:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	KeyMapProvider(uint8_t numberOfRows, uint8_t numberOfColumns);

	virtual uint16_t** getKeyMap();
};

#endif