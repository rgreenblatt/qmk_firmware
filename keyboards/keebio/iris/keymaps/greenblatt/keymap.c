#include QMK_KEYBOARD_H


#define BASE 0 // default layer
#define SY 1 // symbols
#define FUNC_L 2 // function layer


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

  [BASE] = LAYOUT(
  //┌────────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────────────┐
     KC_NO,           KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────────┤
     KC_NO,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────────┤
     LALT_T(KC_MINS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RALT_T(KC_QUOT),
  //├────────────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────────────┤
     KC_NO,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    EML_P,           EML_B,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_NO,
  //└────────────────┴─┬──────┴────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴───┬────┴────────┼────────┴────────┴────────────────┘
                         LGUI_T(KC_TAB), LT(SY, KC_SPC),  LT(FUNC_L, KC_ESC),       LT(FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL)
                  //   └────────────────┴───────────────┴────────────────────┘     └───────────────────┴────────────────┴───────────────┘
  ),

  [SY] = LAYOUT(
  //┌────────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────────────┐
     KC_NO,           KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,                            KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,   KC_NO,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────────┤
     KC_NO,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────────┤
     LALT_T(KC_MINS), KC_EXLM,  KC_AT,   KC_HASH, KC_DLR, KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RALT_T(KC_QUOT),
  //├────────────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────────────┤
     KC_NO,           KC_NO,    KC_LBRC, KC_RBRC, KC_PIPE, KC_BSLS,   EML_P,            EML_B, KC_GRAVE,KC_TILDE,KC_LCBR, KC_RCBR, KC_PLUS, KC_NO,
  //└────────────────┴─┬──────┴────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴───┬────┴────────┼────────┴────────┴────────────────┘
                         LGUI_T(KC_TAB), LT(SY, KC_SPC),  LT(FUNC_L, KC_ESC),       LT(FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL)
                  //   └────────────────┴───────────────┴────────────────────┘     └───────────────────┴────────────────┴───────────────┘
  ),

  [FUNC_L] = LAYOUT(
  //┌────────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────────────┐
     KC_NO,           KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────────┤
     KC_NO,          LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),                LGUI(KC_6),LGUI(KC_7),LGUI(KC_8),LGUI(KC_9),LGUI(KC_0),KC_NO,
  //├────────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────────┤
     LALT_T(KC_MINS), KC_PGUP, KC_PGDOWN, LCTL(KC_U), LCTL(KC_D), KC_PERC,                     KC_LEFT,   KC_DOWN, KC_UP, KC_RIGHT,  KC_RPRN, RALT_T(KC_QUOT),
  //├────────────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────────────┤
     KC_NO,           SGUI(KC_Z),SGUI(KC_X),SGUI(KC_M),SGUI(KC_V),  LGUI(KC_SCLN),   EML_P, EML_B, KC_LEFT,   KC_DOWN, KC_UP, KC_RIGHT, LSFT(KC_ENT), KC_NO,
  //└────────────────┴─┬──────┴────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴───┬────┴────────┼────────┴────────┴────────────────┘
                         LGUI_T(KC_TAB), LT(SY, KC_SPC),  LT(FUNC_L, KC_ESC),       LT(FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL)
                  //   └────────────────┴───────────────┴────────────────────┘     └───────────────────┴────────────────┴───────────────┘
  ),
};
