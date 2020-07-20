/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H

#define BASE 0 // default layer
#define SY 1 // symbols
#define FUNC_L 2 // game_mode
#define GAME_MODE 3 // game_mode
#define GAME_MODE_SY 4 // game_mode symbols

// Blank template at the bottom

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

#ifdef LARGE_FILE
#include "large_file.h"
#undef COND_KEY_1
#define COND_KEY_1 SECRET_1
#endif

#define MACRO_DELAY 0

// #define PSTR

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
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |  BKSP  |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  - _   |   A  |   S  |  D   |   F  |   G  | left |           |right |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  [ {   |   Z  |   X  |   C  |   V  |   B  | Caps |           |  F8  |   N  |   M  | ,  < | . >  | /  ? |  ] }   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .---------.  .--------.                                 .-------.   .---------.
 *                    | Ctrl/= +|  |   SY   |                                 | LShift|   | Ctrl/\  |
 *                    '---------'  | Space  |                                 | Space |   '---------'
 *                                 '--------'                                 '-------'
 *                                        ,-------.                    ,-------.
 *                                        |  GM   |                    |  F11  |
 *                                 ,------|-------|                    |-------|------.
 *                                 | Func |       |                    |       |      |
 *                                 | Esc  | down  |                    | up    | Enter|
 *                                 |      |       |                    |       |      |
 *                                 `--------------'                    `--------------'
 */
#ifdef LARGE_FILE
[BASE] = LAYOUT_gergo(
    KC_TAB,          KC_Q, KC_W, KC_E, KC_R, KC_T,                                                      KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_MINS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_LEFT,                                    KC_RIGHT,  KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LBRC, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_CAPS, COND_KEY_1,  KC_F11, KC_F8, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
    KC_LCTL, KC_SPC, KC_ESC,        KC_DOWN, KC_UP,   KC_ENT, KC_LSHIFT, KC_RCTL
    ),
#else
[BASE] = LAYOUT_gergo(
    KC_TAB,          KC_Q, KC_W, KC_E, KC_R, KC_T,                                                      KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
    LALT_T(KC_MINS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_LEFT,                                    KC_RIGHT,  KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, RALT_T(KC_QUOT),
    LGUI_T(KC_LBRC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_CAPS, TG(GAME_MODE),  KC_F11, KC_F8, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, RGUI_T(KC_RBRC),
    LCTL_T(KC_EQL), LT(SY, KC_SPC), LT(FUNC_L, KC_ESC),        KC_DOWN, KC_UP,   LT(FUNC_L, KC_ENT), SFT_T(KC_SPC), RCTL_T(KC_BSLS)
    ),
#endif
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * | Tab    |   1  |   2  |  3   |   4  |   5  |                         |   6  |   7  |   8  |   9  |   0  |  BKSP  |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  - _   |   !  |   @  |  #   |   $  |   %  | EML  |           |SEC/= |   ^  |   &  |   *  |   (  |   )  |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  [ {   |  F1  |  F2  |  F3  |  F4  |  F5  |USR_N |           |SEC/\ |  F6  |  F7   |  ~   |  `   |  |   |  ] }   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .--------.   .--------.                                 .-------.   .---------.
 *                    | Ctrl/= |   |  BASE  |                                 | LShift|   | Ctrl/\  |
 *                    '--------'   | Space  |                                 | Space |   '---------'
 *                                 '--------'                                 '-------'
 *                                        ,-------.                    ,-------.
 *                                        |  F11  |                    |  F12  |
 *                                 ,------|-------|                    |-------|------.
 *                                 | Func |       |                    |       | Enter|
 *                                 | Esc  |  down |                    |  up   |      |
 *                                 |      |       |                    |       |      |
 *                                 `--------------'                    `--------------'
 */
[SY] = LAYOUT_gergo(
    KC_TAB,          KC_1,    KC_2,  KC_3,    KC_4,   KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_BSPC,
    LALT_T(KC_MINS), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, EML_B,                   COND_KEY_1, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, RALT_T(KC_QUOT),
    LGUI_T(KC_LBRC), KC_F1,   KC_F2, KC_F3,   KC_F4,  KC_F5,   EML_P, KC_WH_U, KC_WH_D, COND_KEY_2, KC_F6,   KC_F7,   KC_TILDE,KC_GRAVE, KC_PIPE, RGUI_T(KC_RBRC),
    LCTL_T(KC_EQL), LT(SY, KC_SPC), LT(FUNC_L, KC_ESC),                      KC_DOWN, KC_UP,                       LT(FUNC_L, KC_ENT), SFT_T(KC_SPC), RCTL_T(KC_BSLS)
    ),

/* Keymap 2: Func layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * | Tab    |   1  |   2  |  3   |   4  |   5  |                         |   6  |   7  |   8  |   9  |   0  |  BKSP  |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  - _   |   !  |   @  |  #   |   $  |   %  | EML  |           |SEC/= |   ^  |   &  |   *  |   (  |   )  |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  [ {   |  F1  |  F2  |  F3  |  F4  |  F5  |USR_N |           |SEC/\ |  F6  |  F7   |  ~   |  `   |  |   |  ] }   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .--------.   .--------.                                 .-------.   .---------.
 *                    | Ctrl/= |   |  BASE  |                                 | LShift|   | Ctrl/\  |
 *                    '--------'   | Space  |                                 | Space |   '---------'
 *                                 '--------'                                 '-------'
 *                                        ,-------.                    ,-------.
 *                                        |  MW U |                    |  MW D |
 *                                 ,------|-------|                    |-------|------.
 *                                 | Func |       |                    |       | Enter|
 *                                 | Esc  |  down |                    |  up   |      |
 *                                 |      |       |                    |       |      |
 *                                 `--------------'                    `--------------'
 */
[FUNC_L] = LAYOUT_gergo(
    KC_TAB, LGUI(KC_1), LGUI(KC_2),  LGUI(KC_3),    LGUI(KC_4),   LGUI(KC_5),                        SGUI(KC_1),    SGUI(KC_2),    SGUI(KC_3),    SGUI(KC_4),     SGUI(KC_5),    KC_BSPC,
    LALT_T(KC_MINS), KC_PGUP, KC_PGDOWN, LCTL(KC_U), LCTL(KC_D), KC_PERC, EML_B,                   COND_KEY_1, KC_LEFT,   KC_DOWN, KC_UP, KC_RIGHT,  KC_RPRN, RALT_T(KC_QUOT),
    LGUI_T(KC_LBRC), SGUI(KC_Z),   SGUI(KC_X), SGUI(KC_M), SGUI(KC_V),  LGUI(KC_SCLN),   EML_P, KC_WH_U, KC_WH_D, COND_KEY_2, KC_LEFT,   KC_DOWN, KC_UP, KC_RIGHT, KC_F9, RGUI_T(KC_RBRC),
    LCTL_T(KC_EQL), LGUI(KC_ENT), LT(FUNC_L, KC_ESC),                      KC_DOWN, KC_UP,                       LT(FUNC_L, KC_ENT), LGUI(KC_ENT), RCTL_T(KC_BSLS)
    ),

/* Keymap template
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
[SYMB] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
 */

/* Keymap template
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
[GAME_MODE] = LAYOUT_gergo(
    KC_TAB,          KC_Q, KC_W, KC_E, KC_R, KC_T,                                     KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_LALT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_TILD,                   KC_EQL,  KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_RALT,
    KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_CAPS, TG(GAME_MODE),  KC_F11, KC_BSLS, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,
    KC_LCTRL, LT(GAME_MODE_SY, KC_SPC), KC_ESC,          KC_DOWN,  KC_UP,                 KC_ENT, KC_SPC, KC_RCTRL
    ),
[GAME_MODE_SY] = LAYOUT_gergo(
    KC_TAB,          KC_1,    KC_2,  KC_3,    KC_4,   KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_BSPC,
    LALT_T(KC_MINS), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, EML_B,                   COND_KEY_1, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, RALT_T(KC_QUOT),
    LGUI_T(KC_LBRC), KC_F1,   KC_F2, KC_F3,   KC_F4,  KC_F5,   EML_P, KC_WH_U, KC_WH_D, COND_KEY_2, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  RGUI_T(KC_RBRC),
    KC_LCTRL, LT(GAME_MODE_SY, KC_SPC), KC_ESC,                      KC_DOWN, KC_UP,                         KC_ENT, SFT_T(KC_SPC), RCTL_T(KC_RIGHT)
    ),
};

// vim:set colorcolumn=:
