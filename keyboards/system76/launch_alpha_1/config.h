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
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

/*
 * Key matrix pins
 * ROWS: AVR pins used for rows, top to bottom
 * COLS: AVR pins used for columns, left to right
 */
#define MATRIX_ROW_PINS { B0, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4, D3, D2, D1, D0, D4, D5 }

/*
 * Diode Direction
 * COL2ROW = COL => Anode (+), ROW => Cathode (-)
 * ROW2COL = ROW => Anode (+), COL => Cathode (-)
 */
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// NKRO must be used
#define FORCE_NKRO

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
