#pragma once

#include <Arduino.h>
#include "KeyCodes.h"
#include "Matrix/Matrix.h"

class BaseKeyboardDescriptor
{
public:
	struct Coordinates
	{
		private:
		uint8_t encodedCoords;

		public:
		Coordinates(uint8_t row, uint8_t column)
		{
			// This assumes that nobody has more than 17 columns.
			this->encodedCoords = 0;
			this->encodedCoords |= (row << 5);
			this->encodedCoords |= column;
		}

		uint8_t getRow()
		{
			return (this->encodedCoords & 0b11100000) >> 5;
		}

		uint8_t getColumn()
		{
			return this->encodedCoords & 0b00011111;
		}
	};

	virtual KeyCode *** createKeyMap() = 0;
	virtual uint8_t getLayersCount() = 0;
	virtual uint8_t getSelectedLayer(Matrix *pressedKeysMatrix) = 0;

	BaseKeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns);
	uint8_t getRowCount();
	uint8_t getColumnCount();
	Coordinates **getCoordinatesMap();
	KeyCode ***getKeyMap();
	KeyType getKeyType(uint8_t layer, uint8_t row, uint8_t column);

protected:
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

	KeyCode ***keymaps;
	Coordinates ** coordMap;
	Coordinates ** createCoordinatesMap(KeyCode ***keymaps);
};