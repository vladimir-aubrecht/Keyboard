#pragma once

#ifdef FEATHER_ESP32_S3_NOPSRAM

#include <Arduino.h>

enum KeyboardKeycode : uint8_t {
    KEY_RESERVED =  0,
    KEY_PAD_0 = 0xEA,
    KEY_PAD_1 = 0xE1,
    KEY_PAD_2 = 0xE2,
    KEY_PAD_3 = 0xE3,
    KEY_PAD_4 = 0xE4,
    KEY_PAD_5 = 0xE5,
    KEY_PAD_6 = 0xE6,
    KEY_PAD_7 = 0xE7,
    KEY_PAD_8 = 0xE8,
    KEY_PAD_9 = 0xE9,
    KEY_PAD_SLASH = 0xDC,
    KEY_PAD_ASTERISK = 0xDD,
    KEY_PAD_MINUS = 0xDE,
    KEY_PAD_PLUS = 0xDF,
    KEY_PAD_ENTER = 0xE0,
    KEY_PAD_PERIOD = 0xEB,

	MEDIA_NEXT	= 0xB5,
	MEDIA_PREVIOUS	= 0xB6,
	MEDIA_PLAY_PAUSE	= 0xCD,
    MEDIA_VOLUME_MUTE	= 0xE2,
	MEDIA_VOLUME_UP	= 0xE9,
	MEDIA_VOLUME_DOWN	= 0xEA,

    KEY_NUM_LOCK = 0,
    KEYPAD_DIVIDE = 0xDC,
    KEYPAD_MULTIPLY = 0xDD,
    KEYPAD_SUBTRACT = 0xDE,
    KEYPAD_ADD = 0xDF,
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
    KEYPAD_DOT = 0xEB,
    KEYPAD_ENTER = 0xE0
};

#endif