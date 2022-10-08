#pragma once

#ifdef TKL

#include "Arduino.h"
#include "IKeyboardDescriptor.h"

class KeyboardDescriptor : public IKeyboardDescriptor
{
private:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;
	KeyCode ***keymaps;
	Coordinates ** coordMap;
	void initKeyAsignment();
	void initCoordinatesMap();
	uint8_t getSelectedLayer(Matrix *pressedKeysMatrix);

public:
	KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns);

	virtual KeyCode ***getKeyMap();
	virtual Coordinates **getCoordinatesMap();
	virtual uint8_t getRowCount();
	virtual uint8_t getColumnCount();
	virtual uint8_t getLayersCount();
};

#endif