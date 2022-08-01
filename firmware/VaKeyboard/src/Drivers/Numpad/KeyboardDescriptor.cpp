#ifdef NUMPAD

#include "KeyboardDescriptor.h"

KeyboardDescriptor::KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;

	this->initKeyAsignment();
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