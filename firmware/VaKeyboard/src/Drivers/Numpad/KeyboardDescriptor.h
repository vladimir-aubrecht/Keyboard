#if defined(NUMPAD)

#pragma once


#include "Arduino.h"
#include "BaseKeyboardDescriptor.h"

class KeyboardDescriptor : public BaseKeyboardDescriptor
{
public:
	KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns);

	uint8_t getSelectedLayer(Matrix *pressedKeysMatrix);
	virtual uint8_t getLayersCount();
	virtual KeyCode *** createKeyMap();
};

#endif