// Copyright 2023 Jason Williams (@wilba)
// SPDX-License-Identifier: GPL-2.0-or-later

// Default layout for WT60-H1
#include QMK_KEYBOARD_H

enum {
        TTILD_HALT,
};


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TTILD_HALT):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TTILD_HALT] = ACTION_TAP_DANCE_TAP_HOLD(KC_TILD, KC_LALT),
};
        

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// Default layer
	[0] = LAYOUT_all(
                KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
                KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
                TD(TTILD_HALT), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
                KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_UP), MO(2),
                KC_LCTL, KC_LGUI, KC_LGUI,                            KC_SPC,                 KC_NO,  LM(2, MOD_LGUI), KC_RGUI, MT(MOD_RCTL, KC_RIGHT)),

	// Fn1 Layer
	[1] = LAYOUT_all(
                KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_DEL,
                KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, RGB_MODE_FORWARD,   RGB_MODE_REVERSE, KC_INS,
                KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, RGB_TOG, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

	// Fn2 Layer
	[2] = LAYOUT_all(
                KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_DEL,
                KC_TILD, KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MODE_FORWARD, RGB_MODE_REVERSE, KC_TRNS,
                KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

};
