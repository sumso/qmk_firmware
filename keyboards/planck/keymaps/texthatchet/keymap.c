/* Copyright 2015-2017 Jack Humbert
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
/* 
  texthatchet - a crude tool, but it'll do the job
  docker run --rm -it -v %CD%/qmk_firmware:/qmk_firmware qmkfm/qmk_firmware   make "planck/light:texthatchet" 
*/
#include QMK_KEYBOARD_H
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOUT,
  _LIN,
  _ROUT,
  _RIN,
  _NUMPAD,
  _MOUSE,
  _MEDIA,
  _SPCL,
  _RAISE,
  _ADJUST,
  _MACRO,
  _EDIT,
  _EDITSP,
  _F1_F10,
  _F11_F20
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  M_EML,
  M_ADDR
};

#define LOWER MO(_NUMPAD)
#define RAISE MO(_RAISE)
#define SPCL LT(_SPCL,KC_SPC)
#define EXIT_LR TO(_QWERTY)

bool has_layer_changed = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Lower| Raise|Backlt|      | Space| Space|Space |Space |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,         KC_Q,           KC_W,           KC_E,          KC_R,          KC_T, KC_Y, LT(_LIN,KC_U), LT(_LIN,KC_I),    LT(_LOUT,KC_O),   KC_P,              KC_BSPC,
    LT(10,KC_CAPS), LT(_ROUT,KC_A), LT(_ROUT,KC_S), LT(_RIN,KC_D), LT(_RIN,KC_F), KC_G, KC_H, LT(_LIN,KC_J), LT(_LIN,KC_K),    LT(_LOUT,KC_L),   LT(_LOUT,KC_QUOT), KC_ENT,
    OSM(MOD_LSFT),  LT(_ROUT,KC_Z), LT(_ROUT,KC_X), LT(_RIN,KC_C), LT(_RIN,KC_V), KC_B, KC_N, LT(_LIN,KC_M), LT(_LIN,KC_COMM), LT(_LOUT,KC_DOT), LT(_LOUT,KC_SLSH), OSM(MOD_RSFT),
    LOWER,          RAISE,          BACKLIT,        KC_NO,         SPCL,          SPCL, SPCL, SPCL,          KC_NO,            KC_NO ,           KC_NO,             KC_NO
),

[_LOUT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, TO(_NUMPAD),    XXXXXXX,       XXXXXXX,    _______, _______,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    XXXXXXX,       TT(_F1_F10),   TT(_F11_F20),  TT(_F11_F20), KC_ENT,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______, OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), OSM(MOD_RCTL), OSM(MOD_RSFT),
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LIN] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, XXXXXXX,       XXXXXXX,       TO(_NUMPAD), _______, _______,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    OSL(_MACRO),   OSL(_MACRO),   TT(_F1_F10), XXXXXXX, KC_ENT ,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______, OSM(MOD_RGUI), OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), OSM(MOD_RSFT),
    _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______, _______, _______
),

[_NUMPAD] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_MINS, _______,
    EXIT_LR, _______, _______, _______, _______, _______, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_ASTR, _______,
    _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_MOUSE] = LAYOUT_planck_grid(
    _______, _______, _______, KC_WH_U, _______, _______, KC_ACL2, _______, KC_MS_U, _______, _______, _______,
    EXIT_LR, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, KC_ACL1, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_ENT ,
    _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, KC_ACL0, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, TO(_MOUSE)
),

[_MEDIA] = LAYOUT_planck_grid( // media keys
    _______, _______, _______, _______, _______, _______, _______, KC_MRWD, KC_VOLU, KC_MFFD, _______, KC_EJCT,
    EXIT_LR, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_MPLY, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MUTE, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_ROUT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, TT(_MEDIA), TT(_MEDIA), TT(_EDIT), TT(_EDIT), _______, _______, _______, _______, _______, _______, _______,
    OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_RIN] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, TT(_MEDIA), _______, TT(_EDIT), TT(_EDIT), _______, _______, _______, _______, _______, _______, _______,
    OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LGUI), _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Edit (D + F)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |      |      |      |      | CUT  |CTL_LF|  UP  |CTL_RT|CTRL_A| Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | EXITL|      | SHIFT|-HOLD-|-HOLD-|      | COPY | LEFT | DOWN | RIGHT| UNDO |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      | PASTE| HOME | DOWN | END  | REDO |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Lower| Raise|Backlt|      | Space| Space|Space |Space |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EDIT] = LAYOUT_planck_grid( // edit layer
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,     LCTL(KC_X),  LCTL(KC_LEFT), KC_UP,   LCTL(KC_RIGHT), LCTL(KC_A), KC_BSPC,
    EXIT_LR, TT(_MEDIA), KC_LSFT, _______, _______,  XXXXXXX,     LCTL(KC_C),  KC_LEFT,       KC_DOWN, KC_RGHT,        LCTL(KC_Z), KC_ENT,
    KC_LSFT, _______, _______, _______, _______,     XXXXXXX,     LCTL(KC_V),  KC_HOME,       KC_DOWN, KC_END,         LCTL(KC_Y), KC_RSFT,
    _______, _______, _______, _______, MO(_EDITSP), MO(_EDITSP), MO(_EDITSP), MO(_EDITSP),   _______, _______,        _______,    _______
),
[_SPCL] = LAYOUT_planck_grid( // space layer
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    TO(_MOUSE), KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_ENT,
    LSFT_T(KC_GRV),  KC_PLUS, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, KC_RSFT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),
[_MACRO] = LAYOUT_planck_grid( // Macro layer
    _______, _______, _______, M_EML,   _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, M_ADDR,  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),
[_EDITSP] = LAYOUT_planck_grid( // edit space layer
    KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,       KC_PGUP, XXXXXXX,      _______, KC_DEL ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, LCTL(KC_HOME), KC_PGDN, LCTL(KC_END), _______, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,       XXXXXXX, XXXXXXX,      _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX
),
[_F1_F10] = LAYOUT_planck_grid( // function keys f1 - f10
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    EXIT_LR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_F11_F20] = LAYOUT_planck_grid( // function keys f11 - f20
    _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
    EXIT_LR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _NUMPAD, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case M_EML:
      if (record->event.pressed) {
        // when keycode M_EML is pressed
        SEND_STRING("email.addr@domainidonthavetotype.com");
      } else {
        // when keycode M_EML is released
      }
      break;
    case M_ADDR:
      if (record->event.pressed) {
        SEND_STRING("12345 987 St. City Province PoS TaL");
      }
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
  rgb_led led;
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    led = g_rgb_leds[i];
    if (led.matrix_co.raw < 0xFF) {
      if (led.modifier) {
          rgb_matrix_set_color( i, red, green, blue );
      }
    }
  }
}
/* LEDS
 * ,-----------------------------------------||-----------------------------------------.
 * |   0  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |  10  |  11  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  12  |  13  |  14  |  15  |  16  |  17  ||  18  |  19  |  20  |  21  |  22  |  23  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  24  |  25  |  26  |  27  |  28  |  29  ||  30  |  31  |  32  |  33  |  34  |  35  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  36  |  37  |  38  |  39  |  40  | 41 | 42 | 43 |  44  |  45  |  46  |  47  |  48  |
 * `-----------------------------------------------------------------------------------'
 */
void rgb_matrix_indicators_user(void) {
	  uint8_t this_led = host_keyboard_leds();
	  //if (!g_suspend_state) {
	    switch (biton32(layer_state)) {
        case _QWERTY:
          //print("q");
          if ( this_led & (1<<USB_LED_NUM_LOCK)) {
            rgb_matrix_set_color(12, 0xFF, 0x00, 0x00);
          } else {
            rgb_matrix_set_color(12, 0x00, 0x00, 0x00);
          }
          rgb_matrix_set_color(13, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(14, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(15, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(16, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(19, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(20, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(21, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(22, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(25, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(26, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(27, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(28, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(31, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(32, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(33, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(34, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(40, 0x16, 0x32, 0x32);
          rgb_matrix_set_color(41, 0x16, 0x32, 0x32);
          rgb_matrix_set_color(42, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(43, 0x16, 0x32, 0x32);
          rgb_matrix_set_color(44, 0x16, 0x32, 0x32);
          break;
        case _LOUT:
          //print("a");
          rgb_matrix_set_color( 11, 0x00, 0x16, 0x00);
          break;
        case _LIN:
          //print("a");
          rgb_matrix_set_color( 10, 0x00, 0x16, 0x00);
          break;
        case _ROUT:
          //print("a");
          rgb_matrix_set_color( 11, 0x00, 0x16, 0x00);
          break;
        case _RIN:
          //print("a");
          rgb_matrix_set_color( 10, 0x00, 0x16, 0x00);
          break;
	      case _NUMPAD:
          //print("l");
	        rgb_matrix_layer_helper(0x00, 0xFF, 0x00, false);
          break;
	      case _RAISE:
          //print("r");
	        rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, false);
          break;
        case _ADJUST:
          //print("a");
          rgb_matrix_layer_helper(0xFF, 0x00, 0x00, false);
          break;
        case _MEDIA:
          //print("a");
          rgb_matrix_set_color( 11, 0x00, 0x16, 0x00);
          break;
        case _SPCL:
          //print("a");
          rgb_matrix_layer_helper(0xFF, 0x00, 0x00, false);
          rgb_matrix_set_color(40, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(41, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(42, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(43, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(44, 0x64, 0x00, 0x00);
          break;
        case _MACRO:
          rgb_matrix_set_color( 3, 0x00, 0x16, 0x00);
          rgb_matrix_set_color( 13, 0x00, 0x16, 0x00);
          break;
        case _EDIT:
          //print("e");
          rgb_matrix_set_color( 6, 0xEF, 0x00, 0x00);
          rgb_matrix_set_color( 7, 0x00, 0x08, 0x00);
          rgb_matrix_set_color( 8, 0x32, 0x32, 0x64);
          rgb_matrix_set_color( 9, 0x00, 0x08, 0x00);
          rgb_matrix_set_color(10, 0x16, 0x00, 0x00);
          rgb_matrix_set_color(12, 0x16, 0x08, 0x16);
          rgb_matrix_set_color(15, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(16, 0x64, 0x00, 0x00);
          rgb_matrix_set_color(18, 0xEF, 0xEF, 0x00);
          rgb_matrix_set_color(19, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(20, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(21, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(22, 0x16, 0x16, 0x00);
          rgb_matrix_set_color(25, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(26, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(27, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(28, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(30, 0x00, 0xEF, 0x00);
          rgb_matrix_set_color(31, 0x00, 0x08, 0x00);
          rgb_matrix_set_color(32, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(33, 0x00, 0x08, 0x00);
          rgb_matrix_set_color(34, 0x00, 0x16, 0x00);
          rgb_matrix_set_color(40, 0x16, 0x32, 0x32);
          rgb_matrix_set_color(41, 0x16, 0x32, 0x32);
          rgb_matrix_set_color(42, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(43, 0x16, 0x32, 0x32);
          rgb_matrix_set_color(44, 0x16, 0x32, 0x32);
          break;
        case _EDITSP:
          rgb_matrix_set_color( 10, 0x00, 0x16, 0x00);
          break;
        case _F1_F10:
          rgb_matrix_set_color( 1, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 2, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 3, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 4, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 5, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 6, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 7, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 8, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color( 9, 0xFF, 0x00, 0xFF);
          rgb_matrix_set_color(10, 0xFF, 0x00, 0xFF);
          break;
        case _F11_F20:
          rgb_matrix_set_color( 1, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 2, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 3, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 4, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 5, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 6, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 7, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 8, 0x39, 0x00, 0x39);
          rgb_matrix_set_color( 9, 0x39, 0x00, 0x39);
          rgb_matrix_set_color(10, 0x39, 0x00, 0x39);
          break;
        case _MOUSE:
          rgb_matrix_set_color( 3, 0x32, 0x32, 0x64);
          rgb_matrix_set_color( 6, 0xEF, 0x9A, 0x00);
          rgb_matrix_set_color( 8, 0x32, 0x64, 0x32);
          rgb_matrix_set_color(12, 0x16, 0x08, 0x16);
          rgb_matrix_set_color(14, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(15, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(16, 0x32, 0x32, 0x64);
          rgb_matrix_set_color(18, 0x5E, 0x3D, 0x00);
          rgb_matrix_set_color(19, 0x32, 0x64, 0x32);
          rgb_matrix_set_color(20, 0x32, 0x64, 0x32);
          rgb_matrix_set_color(21, 0x32, 0x64, 0x32);
          rgb_matrix_set_color(25, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(26, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(27, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(28, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(29, 0x32, 0x32, 0x32);
          rgb_matrix_set_color(30, 0x32, 0x14, 0x00);
          break;
      }
    //}
    if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
      rgb_matrix_set_color(12, 0xFF, 0xFF, 0xFF);
    }

}


bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
