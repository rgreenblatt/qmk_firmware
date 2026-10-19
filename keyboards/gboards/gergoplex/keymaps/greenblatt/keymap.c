/* Copyright 2021 Jane Bernhardt
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

/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 */

#include QMK_KEYBOARD_H

enum {
  _BASE, // default layer
  _SY, // symbols
  _FUNC_L, // function layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Alpha layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |     Q |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |   P   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |     A |  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |   ;   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |     Z |  X  |  C  |  V  |  B  |      |  N  |  M  |  <  |  >  |   /   |
     * `-------------------------------'      `-------------------------------'
     *   .------------------------------.    .----------------------.
     *   | ESC META | ENT ALT | SPC SPE |    | SPC NUM | SHFT | TAB |
     *   '------------------------------'    '----------------------'
     */
    [_BASE] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
             LGUI_T(KC_TAB), LT(_SY, KC_SPC),  LT(_FUNC_L, KC_ESC), LT(_FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL)),

    /* Keymap 1: Special characters layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |    !  |  @  |  {  |  }  |  |  |      |  `  |  ~  |     |     |   \   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    #  |  $  |  (  |  )  | RMB |      |  +  |  -  |  /  |  *  |   '   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    %  |  ^  |  [  |  ]  | LMB |      |  &  |  =  |  ,  |  .  |   -   |
     * `-------------------------------'      `-------------------------------'
     *     .-------------------------.          .-----------------.
     *     | ComboToggle |  ;  |  =  |          |  =  |  ;  | DEL |
     *     '-------------------------'          '-----------------'
     */
    [_SY] = LAYOUT_split_3x5_3(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_EXLM,  KC_AT,   KC_HASH, KC_DLR, KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_QUOT, KC_LBRC, KC_RBRC, KC_UNDERSCORE, KC_MINUS,                     KC_TILDE,KC_PLUS,KC_LCBR, KC_RCBR, KC_DQT,
    LGUI_T(KC_TAB), LT(_SY, KC_SPC),  LT(_FUNC_L, KC_ESC), LT(_FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL)),

    /* Keymap 2: Numbers/Function/Motion layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |   1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F1   | F2  | F3  | F4  | F5  |      | LFT | DWN | UP  | RGT | VOLUP |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F6   | F7  | F8  | F9  | F10 |      | MLFT| MDWN| MUP | MRGT| VOLDN |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .-----------------.
     *             | F11 | F12 |     |          |     | PLY | SKP |
     *             '-----------------'          '-----------------'
     */
    [_FUNC_L] = LAYOUT_split_3x5_3(
    LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),                  SGUI(KC_1),SGUI(KC_2),SGUI(KC_3),SGUI(KC_4),SGUI(KC_5)  ,
    KC_PGUP, KC_PGDN, LCTL(KC_U), LCTL(KC_D), KC_PIPE,                     LALT(KC_H),   LALT(KC_J), LALT(KC_K), LALT(KC_L),  KC_NO,
    KC_BSLS,KC_GRAVE,KC_PIPE,SGUI(KC_V),  LGUI(KC_SCLN),                     KC_LEFT,   KC_DOWN, KC_UP, KC_RIGHT, LSFT(KC_ENT),
    LGUI_T(KC_TAB), LT(_SY, KC_SPC),  LT(_FUNC_L, KC_ESC), LT(_FUNC_L, KC_ENT),  SFT_T(KC_BSPC),  RCTL_T(KC_EQL)),
};
