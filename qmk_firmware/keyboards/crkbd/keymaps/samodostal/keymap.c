/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_COLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_LSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),   MO(2),     KC_LCTL,  KC_SPC, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_COLN, KC_TILD,   KC_AT,  KC_EQL,   KC_GT, KC_AMPR,                      KC_BSLS, KC_DQUO, KC_RPRN, KC_RCBR, KC_RBRC, KC_CIRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_HASH, KC_MINS, KC_SLSH, KC_SCLN,    KC_0,  KC_DLR,                      KC_QUES,    KC_1, KC_LPRN, KC_LCBR, KC_LBRC, KC_PERC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV,    KC_6,    KC_7,    KC_8,    KC_9, KC_PLUS,                      KC_ASTR,    KC_2,    KC_3,    KC_4,    KC_5, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    KC_EXLM, KC_SPC,  KC_UNDS
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,--------------------------------------------------------------------.
        TG(3), XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,                            XXXXXXX, LCTL(KC_A),    LCTL(KC_E), XXXXXXX, KC_RGHT,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------------+-----------+--------------+--------+--------+--------|
      KC_CAPS, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                            XXXXXXX,    KC_LEFT,       XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------------+-----------+--------------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_DOWN,   KC_UP, XXXXXXX,                      LALT(KC_LEFT),    XXXXXXX, LALT(KC_RGHT), KC_VOLD, KC_VOLU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------------+-----------+--------------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TG(3), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_R, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MS_L, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_D, KC_MS_U, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_BTN1, _______,    _______, KC_BTN2, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Dvorak"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Controls"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
0x00, 0x00, 0x18, 0x24, 0xe4, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xe4, 0xe4, 0xfc, 0xfc, 0xfc, 
0xfe, 0xfc, 0xf8, 0xfc, 0x64, 0x24, 0x04, 0x04, 0x04, 0x04, 0x04, 0x84, 0xc4, 0x64, 0x3c, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbc, 0xbc, 0xfe, 0x9e, 0x9e, 0xbc, 
0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xf8, 0xfe, 0x07, 0x03, 0x03, 0x03, 0x03, 0x06, 0x8e, 0xcc, 0x78, 0x70, 0x78, 0xcc, 0x8e, 
0x06, 0x03, 0x03, 0x03, 0x03, 0x07, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 
0x00, 0x00, 0x00, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 
0x07, 0x03, 0x01, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xeb, 0xd1, 0xe0, 0xc0, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf8, 0x3f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 
0x3f, 0xff, 0xfc, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x70, 0x30, 0x18, 0x18, 
0x0c, 0x0c, 0x0f, 0x7e, 0xf6, 0xe6, 0x7e, 0x1e, 0x0f, 0x83, 0xe3, 0xe2, 0xe2, 0xe2, 0xe3, 0x83, 
0x0f, 0x1e, 0x7e, 0xe6, 0xf6, 0x7e, 0x0f, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x70, 0xe0, 0x80, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 
0x00, 0x01, 0x03, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x38, 
0xbe, 0xfe, 0xff, 0x3f, 0xbf, 0xbf, 0xbf, 0x3f, 0x3f, 0xbf, 0xbf, 0x2f, 0x27, 0x03, 0x01, 0x00, 
0x00, 0x80, 0xc0, 0x40, 0x3c, 0x3f, 0x7f, 0xff, 0xe1, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x80, 0xf0, 0x3b, 0x7f, 0x7f, 0x3f, 0x3f, 0xc0, 0x00, 0x00, 0x01, 0x07, 0x0e, 0x0c, 0x18, 0x18, 
0x30, 0x30, 0xf0, 0x7e, 0x6f, 0x67, 0x7e, 0x78, 0xf0, 0xc1, 0xc7, 0x47, 0x47, 0x47, 0xc7, 0xc1, 
0xf0, 0x78, 0x7e, 0x67, 0x6f, 0x7e, 0xf0, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0e, 0x07, 0x01, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 
0xfc, 0xfc, 0xfc, 0xff, 0xc0, 0xc0, 0x80, 0x84, 0x0c, 0x1c, 0x1c, 0x3c, 0x7c, 0xff, 0xff, 0xff, 
0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x0c, 0x0e, 0x07, 0x07, 0x0f, 0x1f, 0x39, 0x7c, 
0x7f, 0x3f, 0x1b, 0x0c, 0x07, 0x03, 0x0b, 0x08, 0x03, 0x00, 0x08, 0x08, 0x0e, 0x00, 0x00, 0x00, 
0x00, 0x0f, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x13, 0x1f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
0x1f, 0x33, 0x20, 0x20, 0x10, 0x08, 0x0c, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x1f, 0x7f, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0x60, 0x71, 0x33, 0x1e, 0x0e, 0x1e, 0x33, 0x71, 
0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe7, 0xc7, 0xc7, 0xe2, 0xe0, 0xe0, 0xf0, 0xff, 0x7f, 0x3f
};
    oled_write_raw_P(crkbd_logo, sizeof(crkbd_logo));
}

void oled_render_wpm(void) {
	char wpm_str[10];
	sprintf(wpm_str, "WPM: %03d", get_current_wpm());
	oled_write_P(PSTR("\n"), false);
	oled_write(wpm_str, false);
} 

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
	oled_render_wpm();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
