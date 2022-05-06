#pragma once

#include <Arduino.h>
#include "KeyCodes.h"

class IKeyMapProvider
{
public:
	virtual KeyboardKeycode** getKeyMap() = 0;
};