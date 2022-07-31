#pragma once

#ifdef NUMPAD

#include "Arduino.h"
#include "IKeyboardDescriptor.h"

class KeyboardDescriptor : public IKeyboardDescriptor
{
public:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns);

	virtual KeyboardKeycode **getKeyMap();
	virtual uint8_t getRowCount();
	virtual uint8_t getColumnCount();
};

#endif