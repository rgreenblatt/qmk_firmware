// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

enum {
  _BASE, // default layer
  _SY, // symbols
  _FUNC_L, // function layer
};

enum customKeycodes {
  SECRET_1 = SAFE_RANGE,
  SECRET_2,
  EML_B,
  EML_P,
};

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#define USE_SECRETS

#include "secrets.h"

#define COND_KEY_1 SECRET_1
#define COND_KEY_2 SECRET_2

#else

#define COND_KEY_1 KC_RIGHT
#define COND_KEY_2 KC_F8

#endif

#define MACRO_DELAY 0

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef LARGE_FILE
        case SECRET_1 ... SECRET_2:
            if (record->event.pressed) {
              send_string_P(LARGE_FILE_STR);
            }
            break;
#else
#ifdef USE_SECRETS
        case SECRET_1 ... SECRET_2:
            if (record->event.pressed) {
              send_string_P(SECRETS[keycode - SECRET_1]);
            }
            break;
#endif
#endif
        case EML_B:
            if (record->event.pressed) {
                SEND_STRING("ryan_greenblatt@brown.edu");
            }
            break;
        case EML_P:
            if (record->event.pressed) {
                SEND_STRING("greenblattryan@gmail.com");
            }
            break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRAVE,  KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
    KC_NO, KC_NO,   KC_LALT, LGUI_T(KC_TAB), LT(_SY, KC_SPC),  LT(_FUNC_L, KC_ESC), LT(_FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL), KC_RALT, KC_NO, KC_NO ),

  /*
   *  !       @     up     {    }        ||     pgup    7     8     9    *
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift bksp ctrl || alt space   fn    .     0    =
   */
  [_SY] = LAYOUT( /* [> RAISE <] */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_EXLM,  KC_AT,   KC_HASH, KC_DLR, KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_QUOT, KC_LBRC, KC_RBRC, KC_UNDERSCORE, KC_MINUS,   KC_GRAVE,  KC_BSLS, KC_TILDE,KC_PLUS,KC_LCBR, KC_RCBR, KC_DQT,
    KC_NO, KC_NO,   KC_LALT, LGUI_T(KC_TAB), LT(_SY, KC_SPC),  LT(_FUNC_L, KC_ESC), LT(_FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL), KC_RALT, KC_NO, KC_NO ),
  /*
   * insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  [_FUNC_L] = LAYOUT( /* [> LOWER <] */
    LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),                  SGUI(KC_1),SGUI(KC_2),SGUI(KC_3),SGUI(KC_4),SGUI(KC_5)  ,
    KC_PGUP, KC_PGDOWN, LCTL(KC_U), LCTL(KC_D), KC_PIPE,                     LALT(KC_H),   LALT(KC_J), LALT(KC_K), LALT(KC_L),  KC_NO,
    KC_BSLS,KC_GRAVE,KC_PIPE,SGUI(KC_V),  LGUI(KC_SCLN),   KC_GRAVE,  KC_BSLS, KC_LEFT,   KC_DOWN, KC_UP, KC_RIGHT, LSFT(KC_ENT),
    KC_NO, KC_NO,   KC_LALT, LGUI_T(KC_TAB), LT(_SY, KC_SPC),  LT(_FUNC_L, KC_ESC), LT(_FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL), KC_RALT, KC_NO, KC_NO ),
};
