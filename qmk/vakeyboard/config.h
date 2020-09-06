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
#define MATRIX_COLS 18

/* key matrix pins */
#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1, F0 }
#define MATRIX_COL_PINS { D6, B7, B6, B5, B4, E6, D7, C6, D4, D0, D1, C7, C7, C7, C7, C7, C7, C7 }
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
