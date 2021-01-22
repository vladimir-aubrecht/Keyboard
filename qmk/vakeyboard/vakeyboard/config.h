#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2040
#define DEVICE_VER      0x0001
#define MANUFACTURER    Vladimir Aubrecht
#define PRODUCT         vakeyboard
#define DESCRIPTION     VA Keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */

#define EXP1_A0 0xC0
#define EXP1_A1 0xC1
#define EXP1_A2 0xC2
#define EXP1_A3 0xC3
#define EXP1_A4 0xC4
#define EXP1_A5 0xC5
#define EXP1_A6 0xC6
#define EXP1_A7 0xC7
#define EXP1_B0 0xC8
#define EXP1_B1 0xC9
#define EXP1_B2 0xCA
#define EXP1_B3 0xCB
#define EXP1_B4 0xCC
#define EXP1_B5 0xCD
#define EXP1_B6 0xCE
#define EXP1_B7 0xCF

#define EXP2_A0 0xD0
#define EXP2_A1 0xD1
#define EXP2_A2 0xD2
#define EXP2_A3 0xD3
#define EXP2_A4 0xE4
#define EXP2_A5 0xE5
#define EXP2_A6 0xE6
#define EXP2_A7 0xE7
#define EXP2_B0 0xE8
#define EXP2_B1 0xE9
#define EXP2_B2 0xEA
#define EXP2_B3 0xEB
#define EXP2_B4 0xEC
#define EXP2_B5 0xED
#define EXP2_B6 0xEE
#define EXP2_B7 0xEF

#define MATRIX_ROW_PINS { EXP2_B0, EXP2_B1, EXP2_B2, EXP2_B3, EXP2_B4, EXP2_B5 } // not used, hardcoded second expander for now
#define MATRIX_COL_PINS { EXP1_A0, EXP1_A1, EXP1_A2, EXP1_A3, EXP1_A4, EXP1_A5, EXP1_A6, EXP1_A7, EXP1_B0, EXP1_B1, EXP1_B2, EXP1_B3, EXP1_B4, EXP1_B5, EXP1_B6, EXP1_B7, EXP2_A0 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

/* disable these deprecated features by default */
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
#define NO_ACTION_TAPPING
