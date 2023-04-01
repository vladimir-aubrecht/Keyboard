#pragma once

#ifdef TINYS2

#include <Arduino.h>

enum KeyboardKeycode : uint8_t {
    KEY_RESERVED =  0,
    KEYPAD_0 = 0xEA,
    KEYPAD_1 = 0xE1,
    KEYPAD_2 = 0xE2,
    KEYPAD_3 = 0xE3,
    KEYPAD_4 = 0xE4,
    KEYPAD_5 = 0xE5,
    KEYPAD_6 = 0xE6,
    KEYPAD_7 = 0xE7,
    KEYPAD_8 = 0xE8,
    KEYPAD_9 = 0xE9,
    KEYPAD_DIVIDE = 0xDC,
    KEYPAD_MULTIPLY = 0xDD,
    KEYPAD_SUBTRACT = 0xDE,
    KEYPAD_ADD = 0xDF,
    KEYPAD_ENTER = 0xE0,
    KEYPAD_DOT = 0xEB,
    KEY_NUM_LOCK = 0x53,

	MEDIA_NEXT	= 0xB5,
	MEDIA_PREVIOUS	= 0xB6,
	MEDIA_PLAY_PAUSE	= 0xCD,
    MEDIA_VOLUME_MUTE	= 0xE2,
	MEDIA_VOLUME_UP	= 0xE9,
	MEDIA_VOLUME_DOWN	= 0xEA,
};

#endif