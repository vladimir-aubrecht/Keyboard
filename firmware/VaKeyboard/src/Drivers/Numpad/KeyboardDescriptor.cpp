#ifdef NUMPAD

#include "KeyboardDescriptor.h"

KeyboardDescriptor::KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;

	this->initKeyAsignment();
	this->initCoordinatesMap();
}

void KeyboardDescriptor::initKeyAsignment()
{
	this->keymaps = new KeyboardKeycode **[this->getLayersCount()];
	
	this->keymaps[0] = new KeyboardKeycode *[this->numberOfRows];
	this->keymaps[0][0] = new KeyboardKeycode[this->numberOfColumns]{KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT};
	this->keymaps[0][1] = new KeyboardKeycode[this->numberOfColumns]{KEYPAD_7, KEYPAD_8, KEYPAD_9, KEY_RESERVED};
	this->keymaps[0][2] = new KeyboardKeycode[this->numberOfColumns]{KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_ADD};
	this->keymaps[0][3] = new KeyboardKeycode[this->numberOfColumns]{KEYPAD_1, KEYPAD_2, KEYPAD_3, KEY_RESERVED};
	this->keymaps[0][4] = new KeyboardKeycode[this->numberOfColumns]{KEYPAD_0, KEY_RESERVED, KEYPAD_DOT, KEYPAD_ENTER};
}

void KeyboardDescriptor::initCoordinatesMap()
{
	this->coordMap = new Coordinates*[0xff - 0x76 + 1];	//registering keys from 0x76 up just becaues I don't have enough of memory on Feather 32u4 for now.

	for (uint8_t layer = 0; layer < 1; layer++)
	{
		for (uint8_t row = 4; row < this->getRowCount(); row++)	//skipping first row just because I don't have enough of memory on Feather 32u4 for now.
		{
			for (uint8_t column = 0; column < this->getColumnCount(); column++)
			{
				KeyboardDescriptor::Coordinates* coord = new KeyboardDescriptor::Coordinates(row, column);
				auto key = this->keymaps[layer][row][column];

				if (key >= 0x76)
				{
					this->coordMap[(uint8_t)key - 0x76] = coord;
				}
			}	
		}
	}
}

KeyboardDescriptor::Coordinates **KeyboardDescriptor::getCoordinatesMap()
{
	return this->coordMap;
}

KeyboardKeycode ***KeyboardDescriptor::getKeyMap()
{
	return keymaps;
}

uint8_t KeyboardDescriptor::getRowCount()
{
	return this->numberOfRows;
}
uint8_t KeyboardDescriptor::getColumnCount()
{
	return this->numberOfColumns;
}

uint8_t KeyboardDescriptor::getLayersCount()
{
	return 1;
}

#endif