/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum {
	TTILD_HLSHIFT,
    TD_1,
    TD_2,
    TD_3,
    TD_4,
    TD_5,
    TD_6,
    TD_7,
    TD_8,
    TD_9,
    TD_0,
    TD_SEMIC,
    TD_QUOTE,
    TD_COM_BSL,
    TD_DOT_FSL,
    TD_HYPHEN,
    TD_EQ,
    TD_LSQ,
    TD_RSQ
};


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

typedef struct {
    uint16_t w;
    uint16_t up;
    uint16_t two;
    uint16_t tapped;
    uint16_t held;
} tap_dance_w_t;

void tap_dance_tap_hold_case_helper(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    action = &tap_dance_actions[TD_INDEX(keycode)];
    if (!record->event.pressed && action->state.count && !action->state.finished) {
        tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
        tap_code16(tap_hold->tap);
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TTILD_HLSHIFT):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_1):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_2):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_3):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_4):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_5):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_6):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_7):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_8):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_9):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_0):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_SEMIC):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_QUOTE):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_COM_BSL):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
    	case TD(TD_DOT_FSL):
    	    tap_dance_tap_hold_case_helper(keycode, record);
    	    break;
	    case TD(TD_HYPHEN):
	        tap_dance_tap_hold_case_helper(keycode, record);
	        break;
        case TD(TD_EQ):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_LSQ):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
        case TD(TD_RSQ):
            tap_dance_tap_hold_case_helper(keycode, record);
            break;
    }
    return true;
}

void tap_dance_tap_hold_unpermissive_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1 && !state->interrupted)
        {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
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

void tap_dance_tap_hold_layer_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            layer_on(tap_hold->hold);
            tap_hold->held = 1;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_layer_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        layer_off(tap_hold->hold);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_HOLD_UP(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_unpermissive_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_LAYER_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_layer_finished, tap_dance_tap_hold_layer_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


tap_dance_action_t tap_dance_actions[] = {
    [TTILD_HLSHIFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_TILD, KC_LSFT),
    [TD_1] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_Q, KC_1),
    [TD_3] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_E, KC_3),
    [TD_4] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_R, KC_4),
    [TD_5] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_T, KC_5),
    [TD_6] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_Y, KC_6),
    [TD_7] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_U, KC_7),
    [TD_8] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_I, KC_8),
    [TD_9] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_O, KC_9),
    [TD_0] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_P, KC_0),
    [TD_2] =  ACTION_TAP_DANCE_TAP_HOLD_UP(KC_W, KC_2),
    [TD_SEMIC] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_K, KC_SCLN),
    [TD_QUOTE] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_L, KC_QUOT),
    [TD_COM_BSL] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_COMM, KC_BSLS),
    [TD_DOT_FSL] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_DOT, KC_SLSH),
    [TD_HYPHEN] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_A, KC_MINS),
    [TD_EQ] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_S, KC_EQUAL),
    [TD_LSQ] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_SPC, KC_LBRC),
    [TD_RSQ] = ACTION_TAP_DANCE_TAP_HOLD_UP(KC_SPC, KC_RBRC)
};

const key_override_t i3_up = ko_make_with_layers_and_negmods(MOD_MASK_GUI, TD(TD_2), RGUI(KC_UP), 1, MOD_MASK_CTRL);
const key_override_t i3_left = ko_make_basic(MOD_MASK_GUI, TD(TD_HYPHEN), RGUI(KC_LEFT));
const key_override_t i3_right = ko_make_basic(MOD_MASK_GUI, KC_D, RGUI(KC_RIGHT));
const key_override_t i3_down = ko_make_basic(MOD_MASK_GUI, TD(TD_EQ), RGUI(KC_DOWN));

const key_override_t lprn = ko_make_basic(MOD_MASK_SHIFT, TD(TD_LSQ), KC_LPRN);
const key_override_t rprn = ko_make_basic(MOD_MASK_SHIFT, TD(TD_RSQ), KC_RPRN);

const key_override_t shift_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &i3_up,
    &i3_down,
    &i3_left,
    &i3_right,
    &shift_del,
    &lprn,
    &rprn,
    NULL // Null terminate the array of overrides!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_ESC,            TD(TD_1),      TD(TD_2),  TD(TD_3),TD(TD_4),TD(TD_5),TD(TD_6),TD(TD_7),TD(TD_8),TD(TD_9),TD(TD_0),    KC_BSPC,
		LT(2, KC_TAB),     TD(TD_HYPHEN), TD(TD_EQ), KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    TD(TD_SEMIC), TD(TD_QUOTE),    KC_ENT,
		TD(TTILD_HLSHIFT), KC_Z,          KC_X, KC_C,KC_V,    KC_B,    KC_N,    KC_M,    TD(TD_COM_BSL), TD(TD_DOT_FSL),  MT(MOD_RSFT, KC_UP),
		KC_LCTL,           KC_LALT, KC_LGUI,         KC_NO,   TD(TD_LSQ),  TD(TD_RSQ),           KC_RGUI, LT(1, KC_RALT), MT(MOD_RCTL, KC_RIGHT)
	),

	[1] = LAYOUT(
		KC_TRNS, KC_PGUP, KC_UP,   KC_PGDN,  KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

	[2] = LAYOUT(
		KC_F1,   KC_F2  , KC_F3,   KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

	[3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

	[4] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

	[5] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

	[6] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

	[7] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
	),

};

