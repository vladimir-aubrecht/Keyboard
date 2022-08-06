#pragma once

#include <Arduino.h>
#include "KeyCodes.h"

class IKeyboardDescriptor
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

	virtual KeyboardKeycode ***getKeyMap() = 0;
	virtual Coordinates **getCoordinatesMap() = 0; 
	virtual uint8_t getRowCount() = 0;
	virtual uint8_t getColumnCount() = 0;
	virtual uint8_t getLayersCount() = 0;
};