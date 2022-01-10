#pragma once

#include <Arduino.h>

class IKeyMapProvider
{
public:
	virtual uint16_t** getKeyMap() = 0;
};