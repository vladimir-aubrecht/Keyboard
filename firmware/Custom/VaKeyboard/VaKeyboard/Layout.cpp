#include "Layout.h"
#include "Keyboard.h"

#define KC_NONE  0x00
#define KC_MENU  0x12
#define KC_PRTSC 0x2C
#define KC_SCRL  0x91
#define KC_PAUSE 0x13

Layout::Layout()
{

}

uint16_t** Layout::getKeymaps()
{
	uint16_t** keymaps = new uint16_t*[6];

	keymaps[0] = new uint16_t[17] { KEY_ESC, KC_NONE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KC_PRTSC, KC_SCRL, KC_PAUSE };
	keymaps[1] = new uint16_t[17]{ '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP };
	keymaps[2] = new uint16_t[17]{ KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\', KEY_DELETE, KEY_END, KEY_PAGE_DOWN };
	keymaps[3] = new uint16_t[17]{ KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', KC_NONE, KEY_RETURN, KC_NONE, KC_NONE, KC_NONE };
	keymaps[4] = new uint16_t[17]{ KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KC_NONE, KEY_RIGHT_SHIFT, KC_NONE, KC_NONE, KEY_UP_ARROW, KC_NONE };
	keymaps[5] = new uint16_t[17]{ KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KC_NONE, KC_NONE, KC_NONE, ' ', KC_NONE, KC_NONE, KC_NONE, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KC_MENU, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW };

	return keymaps;
}