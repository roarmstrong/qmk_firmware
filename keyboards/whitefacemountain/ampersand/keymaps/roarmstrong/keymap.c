// Default layout for Ampersand
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
    TD_MIN_EQ
};


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TTILD_HLSHIFT):  // list all tap dance keycodes with tap-hold configurations
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
    [TTILD_HLSHIFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_TILD, KC_LSFT),
    [TD_1] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_1),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_2),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_3),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_R, KC_4),
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_T, KC_5),
    [TD_6] = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_6),
    [TD_7] = ACTION_TAP_DANCE_DOUBLE(KC_U, KC_7),
    [TD_8] = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_8),
    [TD_9] = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_9),
    [TD_0] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_0),
    [TD_MIN_EQ] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQUAL)
};

const key_override_t i3_up = ko_make_basic(MOD_MASK_GUI, KC_W, RGUI(KC_UP));
const key_override_t i3_left = ko_make_basic(MOD_MASK_GUI, KC_A, RGUI(KC_LEFT));
const key_override_t i3_right = ko_make_basic(MOD_MASK_GUI, KC_D, RGUI(KC_RIGHT));
const key_override_t i3_down = ko_make_basic(MOD_MASK_GUI, KC_S, RGUI(KC_DOWN));

const key_override_t i3_1 = ko_make_basic(MOD_MASK_GUI, TD(TD_1), RGUI(KC_1));
const key_override_t i3_2 = ko_make_basic(MOD_MASK_GUI, TD(TD_2), RGUI(KC_2));
const key_override_t i3_3 = ko_make_basic(MOD_MASK_GUI, TD(TD_3), RGUI(KC_3));
const key_override_t i3_4 = ko_make_basic(MOD_MASK_GUI, TD(TD_4), RGUI(KC_4));
const key_override_t i3_5 = ko_make_basic(MOD_MASK_GUI, TD(TD_5), RGUI(KC_5));

const key_override_t shift_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &i3_up,
    &i3_down,
    &i3_left,
    &i3_right,
    &shift_del,
    &i3_1,
    &i3_2,
    &i3_3,
    &i3_4,
    &i3_5,
    NULL // Null terminate the array of overrides!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_split_bars(
	QK_GESC,  TD(TD_1),TD(TD_2),TD(TD_3),TD(TD_4),TD(TD_5),TD(TD_6),TD(TD_7),TD(TD_8),TD(TD_9),TD(TD_0),TD(TD_MIN_EQ), KC_BSPC,
	KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	TD(TTILD_HLSHIFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_UP),
	KC_LCTL, KC_LALT, KC_LGUI,                      LT(2, KC_SPC),  LT(1, KC_SPC),             KC_RGUI, MO(3), MT(MOD_RCTL, KC_RIGHT)),
[1] = LAYOUT_split_bars(
	KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQUAL, KC_TRNS,
	KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS),
[2] = LAYOUT_split_bars(
	KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS),
[3] = LAYOUT_split_bars(
    KC_ESC,  KC_PGUP, KC_UP, KC_PGDN, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS),
};