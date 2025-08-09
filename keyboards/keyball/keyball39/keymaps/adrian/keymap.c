/*
Copyright 2025 @adrianchong518
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "keyboard.h"
#include QMK_KEYBOARD_H

#include "quantum.h"

enum keymaps { _BASE, _SYM, _NUM, _FN, _NAV };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_right_ball(
    KC_Q          , KC_W          , KC_F          , KC_P          , KC_G                        , KC_J      , KC_L          , KC_U          , KC_Y          , KC_BSPC       ,
    LGUI_T(KC_A)  , LALT_T(KC_R)  , LSFT_T(KC_S)  , LCTL_T(KC_T)  , KC_D                        , KC_H      , RCTL_T(KC_N)  , RSFT_T(KC_E)  , RALT_T(KC_I)  , RGUI_T(KC_O)  ,
    KC_Z          , KC_X          , KC_C          , KC_V          , KC_B                        , KC_K      , KC_M          , KC_ESC        , KC_TAB        , KC_ENT        ,
    XXXXXXX       , XXXXXXX       , XXXXXXX       , TO(_BASE)     , LT(_NAV,KC_SPC)  , XXXXXXX  , MO(_NUM)  , TO(_SYM)      ,                                 XXXXXXX
  ),

  [_NAV] = LAYOUT_right_ball(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_HOME  ,            KC_DOWN  , KC_RIGHT  , KC_BTN3   , XXXXXXX   , XXXXXXX  ,
    KC_LGUI  , KC_LALT  , KC_LSFT  , KC_LCTL  , KC_END   ,            KC_LEFT  , KC_BTN1   , SCRL_MO   , KC_BTN2   , XXXXXXX  ,
    KC_CAPS  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,            KC_UP    , SSNP_HOR  , SSNP_FRE  , SSNP_FRE  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______  , XXXXXXX  , KC_BTN4  , KC_BTN5   ,                         XXXXXXX
  ),

  [_SYM] = LAYOUT_right_ball(
    KC_LT    , KC_GT    , KC_LBRC  , KC_RBRC  , KC_TILD  ,            KC_ASTR  , KC_EQL   , KC_UNDS  , KC_SCLN  , KC_BSPC  ,
    KC_CIRC  , KC_DLR   , KC_LPRN  , KC_RPRN  , KC_AT    ,            KC_BSLS  , KC_COLN  , KC_MINS  , KC_QUOT  , KC_DQT   ,
    KC_PERC  , KC_AMPR  , KC_LCBR  , KC_RCBR  , KC_HASH  ,            KC_EXLM  , KC_QUES  , KC_COMM  , KC_DOT   , KC_SLSH  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______  , KC_LSFT  , _______  , TO(_FN)  ,                       XXXXXXX
  ),

  [_FN] = LAYOUT_right_ball(
    KC_BRID  , KC_BRIU  , KC_VOLD  , KC_VOLU  , KC_MUTE  ,            XXXXXXX  , KC_F12   , KC_F7  , KC_F8  , KC_F9    ,
    KC_LGUI  , KC_LALT  , KC_LSFT  , KC_LCTL  , XXXXXXX  ,            XXXXXXX  , KC_F11   , KC_F4  , KC_F5  , KC_F6    ,
    XXXXXXX  , KC_MPRV  , KC_MPLY  , KC_MNXT  , XXXXXXX  ,            XXXXXXX  , KC_F10   , KC_F1  , KC_F2  , KC_F3    ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______  , XXXXXXX  , _______  , TO(_SYM)  ,                  XXXXXXX
  ),

  [_NUM] = LAYOUT_right_ball(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,            XXXXXXX  , XXXXXXX   , KC_7  , KC_8  , KC_9     ,
    KC_LGUI  , KC_LALT  , KC_LSFT  , KC_LCTL  , XXXXXXX  ,            XXXXXXX  , KC_DEL    , KC_4  , KC_5  , KC_6     ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,            XXXXXXX  , KC_0      , KC_1  , KC_2  , KC_3     ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , XXXXXXX   ,                 XXXXXXX
  ),
};
// clang-format on

void keyboard_post_init_user(void) {
    set_auto_mouse_layer(_NAV);
    set_auto_mouse_enable(true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    // keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
