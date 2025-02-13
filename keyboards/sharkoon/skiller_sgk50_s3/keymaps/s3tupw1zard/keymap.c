// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Globale Variablen zur Speicherung der zuletzt gedrückten Tasten
static uint8_t last_pressed_f13_f18 = 255;  // Ungültige Taste initialisieren
static uint8_t last_pressed_f19_f24 = 255;
static bool music_active = false; // Status von MU_TOG (Musik Toggle)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_HOME, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(1),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_all(
        EE_CLR,  KC_MPLY, KC_MPRV, KC_MNXT, KC_MUTE,  KC_VOLD, KC_VOLU, _______,  _______,  _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______,
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,   KC_F17,  KC_F18,  _______,  _______,  _______, _______, RM_SPDD, RM_SPDU, _______,          RM_SATU,
        _______, _______, _______, _______, _______,  KC_F23,  _______, _______,  _______,  KC_F24,  _______, _______, _______, _______,          RM_SATD,
        _______, _______, KC_F21,  KC_F22,  _______,  _______, _______, _______,  _______,  _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, KC_F19,   _______, _______, _______,  KC_F20,   _______, _______, _______,          _______, RM_VALU, _______,
        _______, GU_TOGG, _______,                             MU_TOGG,                               _______, _______, _______, RM_HUEU, RM_VALD, RM_NEXT
    ),
};

/**
 * RGB-Matrix-Farben anpassen für spezielle Funktionen
 */
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 255, 0, 0);  // Caps Lock auf Rot setzen
    }

    switch (biton32(layer_state)) {
        case 0:  // Layer 0: Tasten statisch einfärben
            rgb_matrix_set_color(10, 0, 255, 0);   // Taste Q grün
            rgb_matrix_set_color(15, 0, 0, 255);   // Taste E blau
            break;
        case 1:  // Layer 1: Zusätzliche Farben
            rgb_matrix_set_color(10, 0, 255, 0);   // Q bleibt grün
            rgb_matrix_set_color(15, 0, 0, 255);   // E bleibt blau
            rgb_matrix_set_color(20, 255, 255, 0); // Taste R gelb
            rgb_matrix_set_color(25, 255, 0, 255); // Taste T pink
            
            // Alle F13-F18 auf eine Basisfarbe setzen
            for (uint8_t i = 0; i < 6; i++) {
                rgb_matrix_set_color(41 + i, 100, 100, 100);  // Standard Grau für F13-F18
            }
            // Die zuletzt gedrückte Taste hervorheben (Rot)
            if (last_pressed_f13_f18 != 255) {
                rgb_matrix_set_color(last_pressed_f13_f18, 255, 0, 0);
            }

            // Alle F19-F24 auf eine Basisfarbe setzen
            for (uint8_t i = 0; i < 6; i++) {
                rgb_matrix_set_color(55 + i, 100, 100, 100);  // Standard Grau für F19-F24
            }
            // Die zuletzt gedrückte Taste hervorheben (Blau)
            if (last_pressed_f19_f24 != 255) {
                rgb_matrix_set_color(last_pressed_f19_f24, 0, 0, 255);
            }

            // Leertaste basierend auf Musikstatus einfärben
            rgb_matrix_set_color(43, music_active ? 0 : 0, music_active ? 255 : 0, music_active ? 0 : 255); 
            break;
    }
    return false;
}

/**
 * Speichert die zuletzt gedrückte F-Taste & Musikstatus
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Prüfen, ob es eine der Tasten F13-F18 ist
        if (keycode >= KC_F13 && keycode <= KC_F18) {
            last_pressed_f13_f18 = 41 + (keycode - KC_F13);
        }
        // Prüfen, ob es eine der Tasten F19-F24 ist
        if (keycode >= KC_F19 && keycode <= KC_F24) {
            last_pressed_f19_f24 = 55 + (keycode - KC_F19);
        }
        // Musikstatus umschalten, wenn MU_TOGG gedrückt wird
        if (keycode == MU_TOGG) {
            music_active = !music_active;
        }
    }
    return true;  // ❗️ WICHTIG: Muss vorhanden sein, damit Tasten funktionieren!
}


