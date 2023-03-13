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
#define MATRIX_ROWS 12 // 6, but each side is separate
#define MATRIX_COLS 16

/*
 * Key matrix pins
 * ROWS: AVR pins used for rows, top to bottom
 * COLS: AVR pins used for columns, left to right
 */
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3 }
#define MATRIX_COL_PINS { D1, B5, D4, C6, D7, E6, B4 }
#define MATRIX_ROW_PINS_RIGHT { F4, F5, F6, F7, B1, B3 }
#define MATRIX_COL_PINS_RIGHT  { D3, D2, D1, B5, D4, C6, D7, E6, B4 }

/*
 * Diode Direction
 * COL2ROW = COL => Anode (+), ROW => Cathode (-)
 * ROW2COL = ROW => Anode (+), COL => Cathode (-)
 */
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// Settings for split keyboard
#define MASTER_RIGHT               // Right half is the master, don't plug USB into left half
#define SOFT_SERIAL_PIN D0         // The halves communicate via serial on pin D0
