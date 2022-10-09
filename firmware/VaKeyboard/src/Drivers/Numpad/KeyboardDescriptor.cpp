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
	this->keymaps = new KeyCode **[this->getLayersCount()];

	this->keymaps[0] = new KeyCode *[this->numberOfRows];
	this->keymaps[0][0] = new KeyCode[this->numberOfColumns]{KEY_RESERVED, KEY_PAD_SLASH, KEY_PAD_ASTERISK, KEY_PAD_MINUS};
	this->keymaps[0][1] = new KeyCode[this->numberOfColumns]{KEY_PAD_7, KEY_PAD_8, KEY_PAD_9, KEY_RESERVED};
	this->keymaps[0][2] = new KeyCode[this->numberOfColumns]{KEY_PAD_4, KEY_PAD_5, KEY_PAD_6, KEY_PAD_PLUS};
	this->keymaps[0][3] = new KeyCode[this->numberOfColumns]{KEY_PAD_1, KEY_PAD_2, KEY_PAD_3, KEY_RESERVED};
	this->keymaps[0][4] = new KeyCode[this->numberOfColumns]{KEY_PAD_0, KEY_RESERVED, KEY_PAD_PERIOD, KEY_PAD_ENTER};
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

uint8_t KeyboardDescriptor::getSelectedLayer(Matrix *pressedKeysMatrix)
{
	return 0;
}

KeyboardDescriptor::Coordinates **KeyboardDescriptor::getCoordinatesMap()
{
	return this->coordMap;
}

KeyCode ***KeyboardDescriptor::getKeyMap()
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