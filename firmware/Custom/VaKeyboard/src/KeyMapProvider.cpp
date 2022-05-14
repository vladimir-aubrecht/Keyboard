#include "KeyMapProvider.h"

KeyMapProvider::KeyMapProvider(uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}
KeyboardKeycode **KeyMapProvider::getKeyMap()
{
	KeyboardKeycode **keymaps = new KeyboardKeycode *[this->numberOfRows];

	keymaps[0] = new KeyboardKeycode[this->numberOfColumns]{KEY_ESC, KEY_RESERVED, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE};
	keymaps[1] = new KeyboardKeycode[this->numberOfColumns]{KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP};
	keymaps[2] = new KeyboardKeycode[this->numberOfColumns]{KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_DELETE, KEY_END, KEY_PAGE_DOWN};
	keymaps[3] = new KeyboardKeycode[this->numberOfColumns]{KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_RESERVED, KEY_RETURN, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED};
	keymaps[4] = new KeyboardKeycode[this->numberOfColumns]{KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RESERVED, KEY_RESERVED, KEY_RIGHT_SHIFT, KEY_RESERVED, KEY_UP_ARROW, KEY_RESERVED};
	keymaps[5] = new KeyboardKeycode[this->numberOfColumns]{KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_SPACE, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_MENU, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW};

	return keymaps;
}