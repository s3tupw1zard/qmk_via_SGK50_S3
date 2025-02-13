// Copyright 2025 s3tupw1zard (@s3tupw1zard)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_profiles {
    PROFILE_NONE = 0,
    PROFILE_MINECRAFT,
    PROFILE_NMS,
    PROFILE_ASKA,
    PROFILE_ELDEN_RING,
    PROFILE_PALWORLD,
};

static enum my_profiles current_profile = PROFILE_NONE;

// Global variables for storing the last pressed keys
static uint8_t last_pressed_f13_f18 = 255;  // Initialize invalid key
static uint8_t last_pressed_f19_f24 = 255;  // Initialize invalid index
static bool music_active = false; // Status of MU_TOGG (Music Toggle)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_HOME, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(1),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_all(
        EE_CLR,  KC_MPLY, KC_MPRV, KC_MNXT, KC_MUTE,  KC_VOLD, KC_VOLU, _______,  _______,  _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______,
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,   KC_F17,  KC_F18,  _______,  _______,  _______, _______, RM_SPDD, RM_SPDU, _______,          RM_SATU,
        _______, _______, _______, _______, _______,  KC_F23,  _______, _______,  _______,  KC_F24,  _______, _______, _______, _______,          RM_SATD,
        _______, _______, KC_F21,  KC_F22,  _______,  _______, _______, _______,  _______,  _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, KC_F19,   _______, _______, _______,  KC_F20,   _______, _______, _______,          _______, RM_VALU, _______,
        _______, GU_TOGG, _______,                             MU_TOGG,                               _______, _______, _______, RM_HUEU, RM_VALD, RM_NEXT
    ),

    [2] = LAYOUT_all(
        _______,  _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, QK_MIDI_NOTE_E_0, _______,  _______,  _______, _______,  _______,  _______,  QK_MIDI_NOTE_D_0, _______, _______, _______,          _______,
        _______, QK_MIDI_NOTE_D_SHARP_0, _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______, _______,          _______,          _______,
        _______, _______, _______, _______, _______,   _______, _______, QK_MIDI_NOTE_C_SHARP_0,  QK_MIDI_NOTE_C_0,   _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                             _______,                               _______, _______, _______, _______, _______, _______
    ),

};

/**
 * Adjust RGB matrix colors for special functions
 */
bool rgb_matrix_indicators_user(void) {

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(81, 255, 0, 0);  // Set caps lock to red
    }

    switch (biton32(layer_state)) {
        case 0:
        // === Normales Layer 0 ===
        // Hier läuft dein normaler Effekt
        // Wir überschreiben nur bestimmte Tasten abhängig vom aktuellen Profil

        switch (current_profile) {
            case PROFILE_MINECRAFT:
                rgb_matrix_set_color(47, 0, 255, 0); // W
                rgb_matrix_set_color(20, 0, 255, 0); // A
                rgb_matrix_set_color(21, 0, 255, 0); // S
                rgb_matrix_set_color(22, 0, 255, 0); // D
                rgb_matrix_set_color(46, 0, 0, 255); // E
                rgb_matrix_set_color(48, 255, 0, 0); // Q
                rgb_matrix_set_color(17, 255, 255, 0); // C
                rgb_matrix_set_color(23, 0, 0, 255); // F
                rgb_matrix_set_color(28, 255, 0, 0); // L
                rgb_matrix_set_color(0, 255, 0, 0); // Space
                rgb_matrix_set_color(84, 0, 255, 0); // Lcontrol
                rgb_matrix_set_color(83, 255, 0, 0); // LShift
                break;

            case PROFILE_NMS:
                rgb_matrix_set_color(47, 0, 255, 0); // W
                rgb_matrix_set_color(20, 0, 255, 0); // A
                rgb_matrix_set_color(21, 0, 255, 0); // S
                rgb_matrix_set_color(22, 0, 255, 0); // D
                rgb_matrix_set_color(46, 0, 0, 255); // E
                rgb_matrix_set_color(48, 255, 0, 0); // Q
                rgb_matrix_set_color(17, 255, 255, 0); // C
                rgb_matrix_set_color(23, 0, 0, 255); // F
                rgb_matrix_set_color(28, 255, 0, 0); // L
                rgb_matrix_set_color(0, 255, 0, 0); // Space
                rgb_matrix_set_color(84, 0, 255, 0); // Lcontrol
                rgb_matrix_set_color(83, 255, 0, 0); // LShift
                break;

            case PROFILE_ASKA:
                rgb_matrix_set_color(47, 0, 255, 0); // W
                rgb_matrix_set_color(20, 0, 255, 0); // A
                rgb_matrix_set_color(21, 0, 255, 0); // S
                rgb_matrix_set_color(22, 0, 255, 0); // D
                rgb_matrix_set_color(46, 0, 0, 255); // E
                rgb_matrix_set_color(48, 255, 0, 0); // Q
                rgb_matrix_set_color(17, 255, 255, 0); // C
                rgb_matrix_set_color(23, 0, 0, 255); // F
                rgb_matrix_set_color(28, 255, 0, 0); // L
                rgb_matrix_set_color(0, 255, 0, 0); // Space
                rgb_matrix_set_color(84, 0, 255, 0); // Lcontrol
                rgb_matrix_set_color(83, 255, 0, 0); // LShift
                break;

            case PROFILE_ELDEN_RING:
                rgb_matrix_set_color(47, 0, 255, 0); // W
                rgb_matrix_set_color(20, 0, 255, 0); // A
                rgb_matrix_set_color(21, 0, 255, 0); // S
                rgb_matrix_set_color(22, 0, 255, 0); // D
                rgb_matrix_set_color(46, 0, 0, 255); // E
                rgb_matrix_set_color(48, 255, 0, 0); // Q
                rgb_matrix_set_color(17, 255, 255, 0); // C
                rgb_matrix_set_color(23, 0, 0, 255); // F
                rgb_matrix_set_color(28, 255, 0, 0); // L
                rgb_matrix_set_color(0, 255, 0, 0); // Space
                rgb_matrix_set_color(84, 0, 255, 0); // Lcontrol
                rgb_matrix_set_color(83, 255, 0, 0); // LShift
                break;

            case PROFILE_PALWORLD:
                rgb_matrix_set_color(47, 0, 255, 0); // W
                rgb_matrix_set_color(20, 0, 255, 0); // A
                rgb_matrix_set_color(21, 0, 255, 0); // S
                rgb_matrix_set_color(22, 0, 255, 0); // D
                rgb_matrix_set_color(46, 0, 0, 255); // E
                rgb_matrix_set_color(48, 255, 0, 0); // Q
                rgb_matrix_set_color(17, 255, 255, 0); // C
                rgb_matrix_set_color(23, 0, 0, 255); // F
                rgb_matrix_set_color(28, 255, 0, 0); // L
                rgb_matrix_set_color(0, 255, 0, 0); // Space
                rgb_matrix_set_color(84, 0, 255, 0); // Lcontrol
                rgb_matrix_set_color(83, 255, 0, 0); // LShift
                break;

            case PROFILE_NONE:
            default:
                // Nichts überschreiben – d.h. nur der normale Effekt
                break;
        }
        break;

        case 1:
            // Set all F13-F18 to red
            rgb_matrix_set_color(49, 255, 0, 0);
            rgb_matrix_set_color(50, 255, 0, 0);
            rgb_matrix_set_color(51, 255, 0, 0);
            rgb_matrix_set_color(52, 255, 0, 0);
            rgb_matrix_set_color(53, 255, 0, 0);
            rgb_matrix_set_color(54, 255, 0, 0);

            // Set all F19-F24 to blue
            rgb_matrix_set_color(17, 0, 0, 255);
            rgb_matrix_set_color(13, 0, 0, 255);
            rgb_matrix_set_color(21, 0, 0, 255);
            rgb_matrix_set_color(22, 0, 0, 255);
            rgb_matrix_set_color(44, 0, 0, 255);
            rgb_matrix_set_color(40, 0, 0, 255);

            // Set color for last pressed key
            if (last_pressed_f13_f18 != 255) {
                rgb_matrix_set_color(last_pressed_f13_f18, 0, 255, 0);
            }
            if (last_pressed_f19_f24 != 255) {
                rgb_matrix_set_color(last_pressed_f19_f24, 0, 255, 0);
            }

            // Color spacebar based on music status
            rgb_matrix_set_color(0, music_active ? 0 : 0, music_active ? 255 : 0, music_active ? 0 : 255);
            break;
        case 2:
            rgb_matrix_set_color(13, 255, 255, 0); // Key: N
            rgb_matrix_set_color(14, 255, 255, 0); // Key: M
            rgb_matrix_set_color(20, 255, 255, 0); // Key: A
            rgb_matrix_set_color(39, 255, 255, 0); // Key: E
            rgb_matrix_set_color(46, 255, 255, 0); // Key: P
            break;
    }
    return false;
}

/**
 * Saves the last pressed F-key & music status
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("Key pressed: row=%d, col=%d, keycode=%d\n",
        record->event.key.row, record->event.key.col, keycode);

    if (record->event.pressed) {

        switch (keycode) {
            case KC_F13: last_pressed_f13_f18 = 49; break;
            case KC_F14: last_pressed_f13_f18 = 50; break;
            case KC_F15: last_pressed_f13_f18 = 51; break;
            case KC_F16: last_pressed_f13_f18 = 52; break;
            case KC_F17: last_pressed_f13_f18 = 53; break;
            case KC_F18: last_pressed_f13_f18 = 54; break;
            case KC_F19: last_pressed_f19_f24 = 17; break;
            case KC_F20: last_pressed_f19_f24 = 13; break;
            case KC_F21: last_pressed_f19_f24 = 21; break;
            case KC_F22: last_pressed_f19_f24 = 22; break;
            case KC_F23: last_pressed_f19_f24 = 44; break;
            case KC_F24: last_pressed_f19_f24 = 40; break;
            case QK_MIDI_NOTE_C_0:
                // Beispiel: Minecraft-Profil aktivieren
                current_profile = PROFILE_MINECRAFT;
                break;

            case QK_MIDI_NOTE_C_SHARP_0:
                // Beispiel: No Man’s Sky-Profil aktivieren
                current_profile = PROFILE_NMS;
                break;

            case QK_MIDI_NOTE_D_SHARP_0:
                // Beispiel: No Man’s Sky-Profil aktivieren
                current_profile = PROFILE_ASKA;
                break;

            case QK_MIDI_NOTE_E_0:
                // Beispiel: No Man’s Sky-Profil aktivieren
                current_profile = PROFILE_ELDEN_RING;
                break;

            case QK_MIDI_NOTE_D_0:
                // Beispiel: No Man’s Sky-Profil aktivieren
                current_profile = PROFILE_PALWORLD;
                break;

        }
        // Toggle music status when MU_TOGG is pressed
        if (keycode == MU_TOGG) {
            music_active = !music_active;
        }
    }
    return true;
}


