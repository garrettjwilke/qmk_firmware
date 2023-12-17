#include QMK_KEYBOARD_H
#define ______ KC_NO

enum layers{
  _BASE,
  _MIDI,
  _PADS,
  _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0, default layer
__________________________________________________________________________________________________________________________________  ________  ___________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        || PRINT  | MEDIA  | PLAY/  | MEDIA  |
|  ESC   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   |  DELETE    ||  HOME  || SCREEN |PREVIOUS| PAUSE  | NEXT   |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________||________|________|________|________|
|        |        |        |        |        |        |        |        |        |        |        |        |        |            ||        || NUM    | NUM    | NUM    | NUM    |
|  ~`    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |  _ -   | =  +   | BACKSPACE  ||  PGUP  || LOCK   | SLASH  |  *     |  -     |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________||________|________|________|________|
|            |        |        |        |        |        |        |        |        |        |        |  [     |   ]    |        ||        || NUM    | NUM    | NUM    |        |
|     TAB    |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  {     |   }    |  |   \ ||  PGDN  ||  7     |  8     |  9     |        |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________||________|________|________| NUM    |
  |            |        |        |        |        |        |        |        |        |        |   ;    |   '    |            |   |        || NUM    | NUM    | NUM    |  +     |
  |    CAPS    |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |   :    |   "    |   ENTER    |   |  END   ||  4     |  5     |  6     |        |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________||________|________|________|________|
  |                |        |        |        |        |        |        |        |   ,    |    .   |   /    |            |        |         | NUM    | NUM    | NUM    |        |
  |     SHIFT      |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   <    |    >   |   ?    |   SHIFT    |   UP   |         |  1     |  2     |  3     |        |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________ |________|________|________| NUM    |
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        ||       NUM       | NUM    | ENTER  |
  |    CTRL    |  LALT  | FN    | LGUI   |    SPACE        |      SPACE      | RCTRL  |  RALT  |     FN      |   |  LEFT  |  DOWN  | RIGHT  ||        0        |  .     |        |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________||_________________|________|________|
*/

  [_BASE] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,       KC_HOME,  KC_PSCR, KC_MPRV, KC_MPLY, KC_MNXT,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,      KC_PGUP,  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_PGDN,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
          KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,       KC_END,   KC_P4,   KC_P5,   KC_P6,
          KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,    KC_UP,           KC_P1,   KC_P2,   KC_P3,   KC_PENT,
          KC_LCTL, KC_LALT, MO(_FUNC), KC_LGUI,     KC_SPC,           KC_SPC,     KC_RCTL,   KC_RALT,   MO(1),         KC_LEFT, KC_DOWN, KC_RGHT,        KC_P0,      KC_PDOT
  ),



  [_MIDI] = LAYOUT(
    MI_C, MI_F,  MI_As,  MI_Ds1,   MI_Gs1,  MI_Cs2,  MI_Fs2, MI_B2,  MI_E3,   MI_A3,  MI_D4,   MI_G4,  MI_C5,   MI_F5,      _______,              _______, _______, _______, _______,
    MI_Cs, MI_Fs, MI_B,   MI_E1,    MI_A1,   MI_D2,   MI_G2,  MI_C3,   MI_F3,  MI_As3, MI_Ds4,  MI_Gs4, MI_Cs5,  MI_Fs5,    MI_OCTU,              _______, _______, _______, _______,
    MI_D,   MI_G,  MI_C1,  MI_F1,     MI_As1, MI_Ds2,  MI_Gs2, MI_Cs3,  MI_Fs3, MI_B3,  MI_E4,   MI_A4,  MI_D5,   MI_G5,    MI_OCTD,              _______, _______, _______, _______,
      MI_Ds, MI_Gs, MI_Cs1,  MI_Fs1,  MI_B1,   MI_E2,   MI_A2,  MI_D3,   MI_G3,  MI_C4,  MI_F4,   MI_As4, MI_Ds5,           _______,               _______, _______, _______,
      MI_E,   MI_A,  MI_D1,   MI_G1,   MI_C2,   MI_F2,   MI_As2, MI_Ds3,   MI_Gs3, MI_Cs4, MI_Fs4, MI_B4,   MI_E5,                         _______, _______, _______, _______,
      _______,   _______, MO(_FUNC), _______, _______,          _______,        _______, _______, _______,         _______, _______, _______,         _______,    _______
  ),

  [_PADS] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,  _______, _______, _______, _______,
    _______, MI_C1, MI_Cs1,  MI_D1, MI_Ds1,  _______, _______,   MI_E2, MI_F2, MI_Fs2, MI_G2, _______, _______,_______,    MI_OCTU,  _______, _______, _______, _______,
    _______,   MI_Gs, MI_A, MI_As, MI_B, _______, _______,      MI_C2, MI_Cs2, MI_D2, MI_Ds2, _______, _______, _______,  MI_OCTD,  _______, _______, _______, _______,
      _______,   MI_E, MI_F, MI_Fs, MI_G, _______, _______,     MI_Gs1, MI_A1, MI_As1, MI_B1, _______, _______,         _______,  _______, _______, _______,
      _______,     MI_C, MI_Cs, MI_D, MI_Ds, _______, _______, MI_E1, MI_F1, MI_Fs1, MI_G1,  _______,       _______,          _______, _______, _______, _______,
      _______,   _______, MO(_FUNC), _______, _______,          _______,        _______, _______, _______,         _______, _______, _______,        _______,    _______
  ),

   /* Layer 1, function layer
__________________________________________________________________________________________________________________________________  ________  ___________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |            || PLAY/  ||        |        |        |        |
| QK_BOOT|        |        |        |        |        |        |        |        |        |        |        |        |            || PAUSE  ||        |        |        |        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________||________|________|________|________|
|        |        |        |        |        |        |        |        |        |        |  LED   |  LED   |  LED   |            || VOLUME ||        |        |        |        |
|        |        |        |        |        |        |        |        |        |        | TOGGLE |  DOWN  |  UP    |            ||   UP   ||        |        |        |        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|____________||________||________|________|________|________|
|            |        |        |        |        |        |        |        |        |        |        |        |        |        || VOLUME ||        |        |        |        |
|PRINT SCREEN|        |        |        |        |        |  HOME  |  PGDN  |  PGUP  |  END   |        |        |        |        ||  DOWN  ||        |        |        |        |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|________||________||________|________|________|        |
  |            |        |        |        |        |        |        |        |        |        |        |        |            |   |        ||        |        |        |        |
  |            |        |        |        |        |        |  LEFT  |  DOWN  |  UP    | RIGHT  |        |        |            |   |  MUTE  ||        |        |        |        |
  |____________|________|________|________|________|________|________|________|________|________|________|________|____________|___|________||________|________|________|________|
  |                |        |        |        |        |        |        |        |        |        |        |            |        |         |        |        |        |        |
  |                |        |        |        |        |        |        |        |        |        |        |            |  PGUP  |         |        |        |        |        |
  |________________|________|________|________|________|________|________|________|________|________|________|____________|________|________ |________|________|________|        |
  |            |        |       |        |                 |                 |        |        |             |   |        |        |        ||                 |        |        |
  |            |        |       |        |                 |                 |        |        |             |   |  HOME  |  PGDN  |  END   ||                 |        |        |
  |____________|________|_______|________|_________________|_________________|________|________|_____________|   |________|________|________||_________________|________|________|
  * 'QK_BOOT' resets the controller and puts the board into firmware flashing mode. If this key is hit accidentally, just unplug the board
  *        and plug it back in.
  */

  [_FUNC] = LAYOUT(
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,    KC_MPLY,  _______, _______, _______, _______,
    TO(_BASE), TO(_MIDI), TO(_PADS), _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_VAD, RGB_VAI, KC_BSPC,      KC_VOLU,  _______, _______, _______, _______,
    _______,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,  KC_P, _______, _______, _______,  KC_VOLD,  _______, _______, _______, _______,
    _______, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L, _______, _______, KC_ENT,      KC_MUTE,  _______, _______, _______,
      KC_LSFT,     KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, _______, _______, _______,       _______,           KC_UP,           _______, _______, _______, _______,
    KC_LCTL,   KC_LALT, _______, KC_LGUI, KC_SPC,          KC_SPC,        _______, _______, _______,           KC_LEFT, KC_DOWN, KC_RIGHT,         _______,    _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
