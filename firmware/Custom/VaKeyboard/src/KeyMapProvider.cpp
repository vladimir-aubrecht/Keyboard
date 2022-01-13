#include "KeyMapProvider.h"
#include "KeyCodes.h"

// codes are 136 + usb hid codes (https://gist.github.com/ekaitz-zarraga/2b25b94b711684ba4e969e5a5723969b)

#define KC_NONE  0x00
#define KC_MENU  0xfe	// not working yet
#define KC_PRTSC 0xce
#define KC_SCRL  0xcf
#define KC_PAUSE 0xd0	// not working yet probably because of soldering

KeyMapProvider::KeyMapProvider(uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}
uint16_t** KeyMapProvider::getKeyMap()
{
	uint16_t** keymaps = new uint16_t*[this->numberOfRows];

	keymaps[0] = new uint16_t[this->numberOfColumns]{ KEY_ESC, KC_NONE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KC_PRTSC, KC_SCRL, KC_PAUSE };
	keymaps[1] = new uint16_t[this->numberOfColumns]{ '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP };
	keymaps[2] = new uint16_t[this->numberOfColumns]{ KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\', KEY_DELETE, KEY_END, KEY_PAGE_DOWN };
	keymaps[3] = new uint16_t[this->numberOfColumns]{ KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', KC_NONE, KEY_RETURN, KC_NONE, KC_NONE, KC_NONE };
	keymaps[4] = new uint16_t[this->numberOfColumns]{ KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KC_NONE, KC_NONE, KEY_RIGHT_SHIFT, KC_NONE, KEY_UP_ARROW, KC_NONE };
	keymaps[5] = new uint16_t[this->numberOfColumns]{ KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KC_NONE, KC_NONE, KC_NONE, ' ', KC_NONE, KC_NONE, KC_NONE, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KC_MENU, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW };

	return keymaps;
}