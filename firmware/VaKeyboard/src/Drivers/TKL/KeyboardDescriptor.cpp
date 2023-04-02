#if defined(TKL)

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

	this->keymaps[0] = new KeyCode*[this->numberOfRows];

	this->keymaps[0][0] = new KeyCode[this->numberOfColumns]{KK_ESC, KK_RESERVED, KK_F1, KK_F2, KK_F3, KK_F4, KK_F5, KK_F6, KK_F7, KK_F8, KK_F9, KK_F10, KK_F11, KK_F12, KK_PRINT, KK_SCROLL_LOCK, KK_PAUSE};
	this->keymaps[0][1] = new KeyCode[this->numberOfColumns]{KK_TILDE, KK_1, KK_2, KK_3, KK_4, KK_5, KK_6, KK_7, KK_8, KK_9, KK_0, KK_MINUS, KK_EQUAL, KK_BACKSPACE, KK_INSERT, KK_HOME, KK_PAGE_UP};
	this->keymaps[0][2] = new KeyCode[this->numberOfColumns]{KK_TAB, KK_Q, KK_W, KK_E, KK_R, KK_T, KK_Y, KK_U, KK_I, KK_O, KK_P, KK_LEFT_BRACE, KK_RIGHT_BRACE, KK_BACKSLASH, KK_DELETE, KK_END, KK_PAGE_DOWN};
	this->keymaps[0][3] = new KeyCode[this->numberOfColumns]{KK_CAPS_LOCK, KK_A, KK_S, KK_D, KK_F, KK_G, KK_H, KK_J, KK_K, KK_L, KK_SEMICOLON, KK_QUOTE, KK_RESERVED, KK_ENTER, KK_RESERVED, KK_RESERVED, KK_RESERVED};
	this->keymaps[0][4] = new KeyCode[this->numberOfColumns]{KK_LEFT_SHIFT, KK_Z, KK_X, KK_C, KK_V, KK_B, KK_N, KK_M, KK_COMMA, KK_PERIOD, KK_SLASH, KK_RESERVED, KK_RESERVED, KK_RIGHT_SHIFT, KK_RESERVED, KK_UP, KK_RESERVED};
	this->keymaps[0][5] = new KeyCode[this->numberOfColumns]{KK_LEFT_CTRL, KK_LEFT_GUI, KK_LEFT_ALT, KK_RESERVED, KK_RESERVED, KK_RESERVED, KK_SPACE, KK_RESERVED, KK_RESERVED, KK_RESERVED, KK_RIGHT_ALT, KK_RIGHT_GUI, KK_MENU, KK_RIGHT_CTRL, KK_LEFT, KK_DOWN, KK_RIGHT};

	this->keymaps[1] = new KeyCode*[this->numberOfRows];
	this->keymaps[1][0] = new KeyCode[this->numberOfColumns]{KK_ESC, KK_RESERVED, KK_F1, KK_F2, KK_F3, KK_F4, KK_F5, KK_F6, KK_PREVIOUS, KK_PLAY_PAUSE, KK_NEXT, KK_VOLUME_MUTE, KK_VOLUME_DOWN, KK_VOLUME_UP, KK_PRINT, KK_SCROLL_LOCK, KK_PAUSE};
	this->keymaps[1][1] = this->keymaps[0][1]; //new KeyCode[this->numberOfColumns]{KK_TILDE, KK_1, KK_2, KK_3, KK_4, KK_5, KK_6, KK_7, KK_8, KK_9, KK_0, KK_MINUS, KK_EQUAL, KK_BACKSPACE, KK_INSERT, KK_HOME, KK_PAGE_UP};
	this->keymaps[1][2] = this->keymaps[0][2]; //new KeyCode[this->numberOfColumns]{KK_TAB, KK_Q, KK_W, KK_E, KK_R, KK_T, KK_Y, KK_U, KK_I, KK_O, KK_P, KK_LEFT_BRACE, KK_RIGHT_BRACE, KK_BACKSLASH, KK_DELETE, KK_END, KK_PAGE_DOWN};
	this->keymaps[1][3] = this->keymaps[0][3]; //new KeyCode[this->numberOfColumns]{KK_CAPS_LOCK, KK_A, KK_S, KK_D, KK_F, KK_G, KK_H, KK_J, KK_K, KK_L, KK_SEMICOLON, KK_QUOTE, KK_RESERVED, KK_RETURN, KK_RESERVED, KK_RESERVED, KK_RESERVED};
	this->keymaps[1][4] = this->keymaps[0][4]; //new KeyCode[this->numberOfColumns]{KK_LEFT_SHIFT, KK_Z, KK_X, KK_C, KK_V, KK_B, KK_N, KK_M, KK_COMMA, KK_PERIOD, KK_SLASH, KK_RESERVED, KK_RESERVED, KK_RIGHT_SHIFT, KK_RESERVED, KK_UP_ARROW, KK_RESERVED};
	this->keymaps[1][5] = this->keymaps[0][5]; //new KeyCode[this->numberOfColumns]{KK_LEFT_CTRL, KK_LEFT_GUI, KK_LEFT_ALT, KK_RESERVED, KK_RESERVED, KK_RESERVED, KK_SPACE, KK_RESERVED, KK_RESERVED, KK_RESERVED, KK_RIGHT_ALT, KK_RIGHT_GUI, HID_KEYBOARD_MENU, KK_RIGHT_CTRL, KK_LEFT_ARROW, KK_DOWN_ARROW, KK_RIGHT_ARROW};
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
	return pressedKeysMatrix->getBit(coordMap[KK_MENU - 0x76]->getRow(), coordMap[KK_MENU - 0x76]->getColumn());
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
	return 2;
}

#endif