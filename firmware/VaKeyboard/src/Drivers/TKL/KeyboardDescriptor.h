#pragma once

#ifdef TKL

#include "Arduino.h"
#include "IKeyboardDescriptor.h"

class KeyboardDescriptor : public IKeyboardDescriptor
{
private:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;
	KeyboardKeycode ***keymaps;
	Coordinates ** coordMap;
	void initKeyAsignment();
	void initCoordinatesMap();

public:
	KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns);

	virtual KeyboardKeycode ***getKeyMap();
	virtual Coordinates **getCoordinatesMap();
	virtual uint8_t getRowCount();
	virtual uint8_t getColumnCount();
	virtual uint8_t getLayersCount();
};

#endif