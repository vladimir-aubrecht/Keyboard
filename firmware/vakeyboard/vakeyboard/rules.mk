# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

AUDIO_ENABLE = no
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
COMMAND_ENABLE = no     # Commands for debug and configuration
CONSOLE_ENABLE = yes    # Console for debug
DEBUG_ENABLE = yes
EXTRAKEY_ENABLE = no	# Audio control and System control
MOUSEKEY_ENABLE = no	# Mouse keys
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = no
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
UNICODE_ENABLE = yes
TAP_DANCE_ENABLE = no
BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
CUSTOM_MATRIX = lite

SRC += \
		matrix.c \
		expander.c \
		matrix_expander.c
QUANTUM_LIB_SRC += i2c_master.c
