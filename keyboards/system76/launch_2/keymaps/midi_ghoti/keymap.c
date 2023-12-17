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

#include QMK_KEYBOARD_H
#define _______ KC_NO
#define _BASE 0
#define _GHOTI 1
#define _PADS 2
#define _FUNC 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  /* BASE layer
 _________________________________________________________________________________________________________________________________  ________
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        |
|  ESC   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   | BACKSPACE  ||  HOME  |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|   ~    |   !    |   @    |   #    |   $    |   %    |   ^    |   &    |   *    |   (    |   )    |   _    |   +    |            ||        |
|   `    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   -    |   =    | BACKSPACE  ||  PGUP  |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|            |        |        |        |        |        |        |        |        |        |        |  [     |   ]    |   |    ||        |
|     TAB    |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  {     |   }    |   \    ||  PGDN  |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________|
  |            |        |        |        |        |        |        |        |        |        |   :    |   "    |            |   |        |
  |  BACKSPACE |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |   ;    |   '    |   ENTER    |   |  END   |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________|
  |                |        |        |        |        |        |        |        |   <    |    >   |   ?    |            |        |
  |     SHIFT      |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   ,    |    .   |   /    |   SHIFT    |   UP   |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        |
  |    CTRL    |  FN    | LALT  | LGUI   |    SPACE        |      SPACE      | RCTRL  |  RALT  |             |   |  LEFT  |  DOWN  | RIGHT  |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________|
   */

  [_BASE] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,    KC_HOME,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_PGUP,
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_PGDN,
      KC_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,          KC_END,
      KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT,   KC_UP,
      KC_LCTL,   KC_LALT,  MO(_FUNC), KC_LGUI, KC_SPC,           KC_SPC,           KC_RCTL, KC_RALT, KC_NO,       KC_LEFT, KC_DOWN, KC_RGHT
  ),

    /* GHOTI layer
 _________________________________________________________________________________________________________________________________  ________
|        |        |        |        |        |        |        |        |        |        |        |        |        |     DEL    ||        |
|        |        |        |        |        |        |        |        |        |        |        |        |        |     KEY    ||        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|        |        |        |        |        |        |        |        |        |        |  LED   |  LED   |  LED   |     DEL    || VOLUME |
|        |        |        |        |        |        |        |        |        |        | TOGGLE |  DOWN  |  UP    |     DEL    ||   UP   |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|            |        |        |        |        |        |        |        |        |        |        |        |        |        || VOLUME |
|            |        |        |        |        |        |        |        |        |        |        |        |        |        ||  DOWN  |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________|
  |            |        |        |        |        |        |        |        |        |        |        |        |            |   |  STOP  |
  |            |        |        |        |        |        |        |        |        |        |        |        |            |   |  MIDI  |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|__NOTES_|
  |                |        |        |        |        |        |        |        |        |        |        |            |        |
  |                |        |        |        |        |        |        |        |        |        |        |            |        |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        |
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________|

   */

  [_GHOTI] = LAYOUT(
    MI_C, MI_F,  MI_As,  MI_Ds1,   MI_Gs1,  MI_Cs2,  MI_Fs2, MI_B2,  MI_E3,   MI_A3,  MI_D4,   MI_G4,  MI_C5,   MI_F5,    _______,
    MI_Cs, MI_Fs, MI_B,   MI_E1,    MI_A1,   MI_D2,   MI_G2,  MI_C3,   MI_F3,  MI_As3, MI_Ds4,  MI_Gs4, MI_Cs5,  MI_Fs5,    MI_OCTU,
      MI_D, MI_G,  MI_C1,  MI_F1,     MI_As1, MI_Ds2,  MI_Gs2, MI_Cs3,  MI_Fs3, MI_B3,  MI_E4,   MI_A4,  MI_D5,   MI_G5,    MI_OCTD,
      MI_Ds, MI_Gs, MI_Cs1,  MI_Fs1,  MI_B1,   MI_E2,   MI_A2,  MI_D3,   MI_G3,  MI_C4,  MI_F4,   MI_As4, MI_Ds5,         _______,
      MI_E,   MI_A,  MI_D1,   MI_G1,   MI_C2,   MI_F2,   MI_As2, MI_Ds3,   MI_Gs3, MI_Cs4, MI_Fs4, MI_B4,   MI_E5,
      _______,   _______, MO(_FUNC), _______, _______,          _______,        _______, _______, _______,         _______, _______, _______
  ),


    /* MIDI Pads layer
 _________________________________________________________________________________________________________________________________  ________
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        |
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        |
|        |    C   |   C#   |    D   |   D#   |        |        |        |        |   E1   |   F1   |   F#1  |   G1   |            ||        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
|            |        |        |        |        |        |        |        |        |        |        |        |        |        ||        |
|            |    E   |    F   |   F#   |    G   |        |        |        |   G#1  |   A1   |   A#1  |   B1   |        |        ||        |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________|
  |            |        |        |        |        |        |        |        |        |        |        |        |            |   |        |
  |            |    G#  |    A   |    A#  |    B   |        |        |   C2   |   C#2  |   D2   |   D#2  |        |            |   |        |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________|
  |                |        |        |        |        |        |        |        |        |        |        |            |  MIDI  |
  |                |   C1   |   C#1  |   D1   |   D#1  |        |   E2   |   F2   |   F#2  |   G2   |        |            | OCTAVE |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|___UP___|________
  |            | ACCESS |       |        |                 |                 |        |        |             |   |        |  MIDI  |        |
  |            | FUNC   |       |        |                 |                 |        |        |             |   |        | OCTAVE |        |
  |____________|_LAYER__|_______|________|_________________|_________________|________|________|_____________|   |________|__DOWN__|________|

   */

  [_PADS] = LAYOUT(
    _______, _______,  _______, _______,  _______, _______,  _______,   _______, _______, _______, _______, _______, _______, _______,    _______,
    _______, MI_C1, MI_Cs1,  MI_D1, MI_Ds1,  _______, _______,   MI_E2, MI_F2, MI_Fs2, MI_G2, _______, _______,_______,    MI_OCTU,
    _______,   MI_Gs, MI_A, MI_As, MI_B, _______, _______,      MI_C2, MI_Cs2, MI_D2, MI_Ds2, _______, _______, _______,  MI_OCTD,
      _______,   MI_E, MI_F, MI_Fs, MI_G, _______, _______,     MI_Gs1, MI_A1, MI_As1, MI_B1, _______, _______,         _______,
      _______,     MI_C, MI_Cs, MI_D, MI_Ds, _______, _______, MI_E1, MI_F1, MI_Fs1, MI_G1,  _______,       _______,
      _______,   _______, MO(_FUNC), _______, _______,          _______,        _______, _______, _______,         _______, _______, _______
  ),

    /* Functions layer
 _________________________________________________________________________________________________________________________________  ________
|        |        |        |        |        |        |        |        |        |        |        |        |        |     DEL    ||        |
|        |        |        |        |        |        |        |        |        |        |        |        |        |     KEY    ||        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________|
| SWITCH | SWITCH | SWITCH |        |        |        |        |        |        |        |  LED   |  LED   |  LED   |     DEL    || VOLUME |
|   TO   |   TO   |   TO   |        |        |        |        |        |        |        | TOGGLE |  DOWN  |  UP    |     DEL    ||   UP   |
|_QWERTY_|__MIDI1_|__PADS__|________|________|________|________|________|________|________|________|________|________|____________||________|
|            |        |        |        |        |        |        |        |        |        |        |        |        |        || VOLUME |
|            |        |        |        |        |        |        |        |        |        |        |        |        |        ||  DOWN  |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________|
  |            |        |        |        |        |        |        |        |        |        |        |        |            |   |  MIDI  |
  |     CAPS   |        |        |        |        |        |        |        |        |        |        |        |            |   |  OFF   |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________|
  |                |        |        |        |        |        |        |        |        |        |        |            |        |
  |                |        |        |        |        |        |        |        |        |        |        |            |        |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        |
  |    LCTL    |        | LALT  | SUPER  |      SPACE      |      SPACE      |        |        |             |   |        |        |        |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________|

   */


  [_FUNC] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BRID, KC_BRIU,              KC_DEL,     _______,
    TO(_BASE), TO(_GHOTI), TO(_PADS), _______,  _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_VAD, RGB_VAI,  KC_BSPC,     KC_VOLU,
    _______,   _______, _______, _______, KC_R, _______, _______, _______, _______, KC_O,  _______, _______, _______, _______,              KC_VOLD,
      _______,   KC_A, KC_S, _______, _______, _______, _______, _______, _______,   _______, _______, _______, KC_ENT,         MI_AOFF,
      KC_LSFT,     KC_Z, KC_X, KC_C, KC_V, _______, _______, _______, _______, _______, _______,       _______,           KC_UP,
      KC_LCTL,   KC_LALT, _______, KC_LGUI, KC_SPC,          KC_SPC,        _______, _______, _______,           KC_LEFT, KC_DOWN, KC_RIGHT
  ),

};

