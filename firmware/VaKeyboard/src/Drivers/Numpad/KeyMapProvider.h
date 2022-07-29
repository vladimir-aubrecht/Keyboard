#pragma once

#ifdef NUMPAD

#include "Arduino.h"
#include "IKeyMapProvider.h"

class KeyMapProvider : public IKeyMapProvider
{
public:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	KeyMapProvider(uint8_t numberOfRows, uint8_t numberOfColumns);

	virtual KeyboardKeycode **getKeyMap();
	virtual uint8_t getRowCount();
	virtual uint8_t getColumnCount();
};

#endif