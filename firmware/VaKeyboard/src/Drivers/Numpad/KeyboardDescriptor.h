#pragma once

#ifdef NUMPAD

#include "Arduino.h"
#include "IKeyboardDescriptor.h"

class KeyboardDescriptor : public IKeyboardDescriptor
{
public:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;
	KeyCode ***keymaps;
	Coordinates ** coordMap;
	void initKeyAsignment();
	void initCoordinatesMap();

public:
	KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns);

	virtual KeyCode ***getKeyMap();
	virtual Coordinates **getCoordinatesMap();
	virtual uint8_t getRowCount();
	virtual uint8_t getColumnCount();
	virtual uint8_t getLayersCount();
};

#endif