/* Copyright 2021 kapows
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Layer shorthand
#define AL_ 0u
#define BL_ 1u
#define CL_ 2u
#define DL_ 3u

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [AL_] = LAYOUT_tkl_ansi( // Base
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_SCRL,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        MO(BL_),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,                      KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(DL_),  KC_APP,   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [BL_] = LAYOUT_tkl_ansi( // Right Cluster and Function Row
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_END,   KC_MPLY,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LALT,  KC_LCTL,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_DEL,   XXXXXXX,  _______, 
        _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PGUP,  KC_PGDN,  XXXXXXX,  _______,                      XXXXXXX,
        _______,  _______,  _______,                                KC_BSPC,                                _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
    [CL_] = LAYOUT_tkl_ansi( // 
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
    [DL_] = LAYOUT_tkl_ansi( // Default function keys
        XXXXXXX,  KC_MPLY,  KC_MSTP,  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  CM_TOGG,            XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_CAPS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
};
// clang-format on

// I have previously experimented with mod-taps and though they worked,
// it made typing very janky and laggy when hitting those keys and I
// don't like that.
//
// I have previously experimented with triple key combos and though
// they worked they were very straining on the hand. I kept pressing
// all three really hard.
//
// I think overall two key combos work better.
enum COMBOS {
  DF_COMBO = 0,
  SD_COMBO,
  SF_COMBO,
  JK_COMBO,
  KL_COMBO,
  JL_COMBO,

  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM sf_combo[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};

// custom modifier keycodes because the actual mod press is
// undesirable for my purposes.
enum custom_keycodes {
  KP_LCTL = SAFE_RANGE,
  KP_LALT,
  KP_LCTL_LALT,
  KP_RCTL,
  KP_RALT,
  KP_RCTL_RALT,
};

combo_t key_combos[] = {
    [SD_COMBO] = COMBO(sd_combo, KP_LALT),
    [DF_COMBO] = COMBO(df_combo, KP_LCTL),
    [SF_COMBO] = COMBO(sf_combo, KP_LCTL_LALT),
    [JK_COMBO] = COMBO(jk_combo, KP_RCTL),
    [KL_COMBO] = COMBO(kl_combo, KP_RALT),
    [JL_COMBO] = COMBO(jl_combo, KP_RCTL_RALT),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool pressed = record->event.pressed;
  switch (keycode) {
  case KP_LCTL:
    if (pressed) {
      add_mods(MOD_BIT(KC_LCTL));
    } else {
      unregister_mods(MOD_BIT(KC_LCTL));
    }
    break;
  case KP_LALT:
    if (pressed) {
      add_mods(MOD_BIT(KC_LALT));
    } else {
      unregister_mods(MOD_BIT(KC_LALT));
    }
    break;
  case KP_LCTL_LALT:
    if (pressed) {
      add_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    } else {
      unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    }
    break;
  case KP_RCTL:
    if (pressed) {
      add_mods(MOD_BIT(KC_RCTL));
    } else {
      unregister_mods(MOD_BIT(KC_RCTL));
    }
    break;
  case KP_RALT:
    if (pressed) {
      add_mods(MOD_BIT(KC_RALT));
    } else {
      unregister_mods(MOD_BIT(KC_RALT));
    }
    break;
  case KP_RCTL_RALT:
    if (pressed) {
      add_mods(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT));
    } else {
      unregister_mods(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT));
    }
    break;
  default:
    break;
  }
  return true;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
  switch (index) {
  default:
    return COMBO_TERM;
  }
}

// Default false allows on finger combo hold.
bool process_combo_key_release(uint16_t index, combo_t *combo,
                               uint8_t key_index, uint16_t keycode) {
  return false;
}

// At the moment I don't want any of my combos to be tap only.
bool get_combo_must_tap(uint16_t index, combo_t *combo) { return false; }

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
  switch (index) {
  default:
    return true;
  }
}

// clang-format off
uint16_t left_keys[] = {
KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6, 
KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y, 
MO(BL_),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H, 
KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B, 
KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC
};
uint16_t right_keys[] = {
KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,           
KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           
          KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,          
KC_SPC,                                 KC_RALT,  MO(DL_),  KC_APP,   KC_RCTL   
};
// clang-format on
int const left_keys_size = sizeof(left_keys) / sizeof(left_keys[0]);
int const right_keys_size = sizeof(right_keys) / sizeof(right_keys[0]);
bool includes_keycode(uint16_t keycodes[], int size, uint16_t keycode) {
  for (int i = 0; i < size; ++i) {
    if (keycode == keycodes[i]) {
      return true;
    }
  }
  return false;
}

bool permissive_combo_key(uint16_t index, combo_t *combo, uint16_t keycode,
                          keyrecord_t *record) {
  if (!record->event.pressed) {
    return false;
  }
  switch (index) {
  case SD_COMBO:
  case SF_COMBO:
  case DF_COMBO:
    return includes_keycode(right_keys, right_keys_size, keycode);
    break;
  case JK_COMBO:
  case JL_COMBO:
  case KL_COMBO:
    return includes_keycode(left_keys, left_keys_size, keycode);
  default:
    return false;
  }
}
