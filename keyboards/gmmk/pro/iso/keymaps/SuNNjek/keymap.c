/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

#include "keymap.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt        Rotary(Play/Pause)
//      ^        1        2        3        4        5        6        7        8        9        0        ß        '        BackSpc           Del
//      Tab      Q        W        E        R        T        Z        U        I        O        P        Ü        +                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        Ö        Ä        #        Enter             PgDn
//      Sh_L     <        Y        X        C        V        B        N        M        ,        .        -                 Sh_R     Up       Ins
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MPLY,
        DE_CIRC, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS,   DE_ACUT, KC_BSPC,          KC_INS,
        KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UDIA, DE_PLUS,                   KC_DEL,
        KC_CAPS, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L,    DE_ODIA, DE_ADIA, DE_HASH, KC_ENT,           KC_PGUP,
        KC_LSFT, DE_LABK, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BRK,           RGB_TOG,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, KC_END,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Turning the rotary encoder controls backlight brightness
    switch(get_highest_layer(layer_state)) {
        default:
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;

#ifdef RGB_MATRIX_ENABLE
        case 1:
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
            break;
#endif
    }
    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        set_rgb_caps_leds(RGB_ORANGE);
    } else {
        rgb_matrix_enable();
    }
}

void set_rgb_caps_leds(uint8_t r, uint8_t g, uint8_t b) {
    rgb_matrix_set_color(68, r, g, b); // Left side LED 1
    rgb_matrix_set_color(69, r, g, b); // Right side LED 1
    rgb_matrix_set_color(71, r, g, b); // Left side LED 2
    rgb_matrix_set_color(72, r, g, b); // Right side LED 2
    rgb_matrix_set_color(74, r, g, b); // Left side LED 3
    rgb_matrix_set_color(75, r, g, b); // Right side LED 3
    rgb_matrix_set_color(77, r, g, b); // Left side LED 4
    rgb_matrix_set_color(78, r, g, b); // Right side LED 4
    rgb_matrix_set_color(81, r, g, b); // Left side LED 5
    rgb_matrix_set_color(82, r, g, b); // Right side LED 5
    rgb_matrix_set_color(84, r, g, b); // Left side LED 6
    rgb_matrix_set_color(85, r, g, b); // Right side LED 6
    rgb_matrix_set_color(88, r, g, b); // Left side LED 7
    rgb_matrix_set_color(89, r, g, b); // Right side LED 7
    rgb_matrix_set_color(92, r, g, b); // Left side LED 8
    rgb_matrix_set_color(93, r, g, b); // Right side LED 8
    rgb_matrix_set_color(0,  r, g, b); // ESC LED
}
#endif
