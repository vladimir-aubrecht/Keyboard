#pragma once
#ifdef WROOM32
#include <Arduino.h>
enum KeyboardKeycode : uint8_t {
	MEDIA_NEXT	= 0xB5,
	MEDIA_PREVIOUS	= 0xB6,
	MEDIA_PLAY_PAUSE	= 0xCD,
    MEDIA_VOLUME_MUTE	= 0xE2,
	MEDIA_VOLUME_UP	= 0xE9,
	MEDIA_VOLUME_DOWN	= 0xEA,
    KEY_RESERVED        =  0,
    KEY_1               = 30,
    KEY_2               = 31,
    KEY_3               = 32,
    KEY_4               = 33,
    KEY_5               = 34,
    KEY_6               = 35,
    KEY_7               = 36,
    KEY_8               = 37,
    KEY_9               = 38,
    KEY_0               = 39,
    KEY_ENTER           = 40,
    KEY_MINUS           = 45,
    KEY_PERIOD          = 55,
    KEY_SLASH           = 56,
    KEY_NUM_LOCK        = 0x53,
    KEYPAD_MULTIPLY     = 0x55,
    KEYPAD_ADD          = 0x57,
    KEYPAD_ENTER        = 0x58,
    HID_KEYBOARD_MENU   = 0x76
};
#endif