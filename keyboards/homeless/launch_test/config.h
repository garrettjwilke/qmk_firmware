/*
 *  Copyright (C) 2021  System76
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

// key matrix size
#define MATRIX_ROWS 2
#define MATRIX_COLS 11

/*
 * Key matrix pins
 * ROWS: AVR pins used for rows, top to bottom
 * COLS: AVR pins used for columns, left to right
 */
#define MATRIX_ROW_PINS { F0, F1 }
#define MATRIX_COL_PINS { C6, B6, B5, B4, D7, D6, D4, D5, D3, D2, B7 }

/*
 * Diode Direction
 * COL2ROW = COL => Anode (+), ROW => Cathode (-)
 * ROW2COL = ROW => Anode (+), COL => Cathode (-)
 */
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DI_PIN E6
#    define RGB_MATRIX_LED_COUNT 22
#    define RGB_MATRIX_KEYPRESSES                                      // Reacts to keypresses
// #    define RGB_MATRIX_KEYRELEASES                                     // Reacts to keyreleases (instead of keypresses)
// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS                             // Enables framebuffer effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED                             // Turns off effects when suspended
// Limit brightness to support USB-A at 0.5 A
// TODO: Do this dynamically based on power source
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 176                          // Limits maximum brightness of LEDs to 176 out of 255. If not defined, maximum brightness is set to 255
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Sets the default mode, if none has been set
#    define RGB_MATRIX_DEFAULT_HUE 142                                 // Sets the default hue value, if none has been set
#    define RGB_MATRIX_DEFAULT_SAT 255                                 // Sets the default saturation value, if none has been set
#    define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS       // Sets the default brightness value, if none has been set
#    define RGB_MATRIX_DEFAULT_SPD 127                                 // Sets the default animation speed, if none has been set
#    define RGB_MATRIX_DISABLE_KEYCODES                                // Disables control of rgb matrix by keycodes (must use code functions to control the feature)

#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#endif  // RGB_MATRIX_ENABLE

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// Dynamic keyboard support {
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM usage
#define EEPROM_SIZE 1024

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x76EC
#define EEPROM_MAGIC_ADDR 64
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x01
#define EEPROM_VERSION_ADDR (EEPROM_MAGIC_ADDR + 2)

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR (EEPROM_VERSION_ADDR + 1)
#define DYNAMIC_KEYMAP_EEPROM_SIZE (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2)
// Dynamic macro starts after dynamic keymaps
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + DYNAMIC_KEYMAP_EEPROM_SIZE)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (EEPROM_SIZE - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR)
#define DYNAMIC_KEYMAP_MACRO_COUNT 16
// } Dynamic keyboard support
