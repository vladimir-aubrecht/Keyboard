#pragma once

#include <Arduino.h>
#include "KeyCodes.h"

class IKeyboardDescriptor
{
public:
	virtual KeyboardKeycode ***getKeyMap() = 0;
	virtual uint8_t getRowCount() = 0;
	virtual uint8_t getColumnCount() = 0;
	virtual uint8_t getLayersCount() = 0;
};