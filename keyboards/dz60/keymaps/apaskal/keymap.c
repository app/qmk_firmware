#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV, 
		KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, 
		F(0),    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, F(1), 
		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_DEL, 
		KC_NO,   KC_LGUI, KC_LALT, MO(1), KC_SPC, MO(1), KC_RALT, KC_RCTL , KC_NO, MO(2), KC_NO),

	KEYMAP(
		KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_TRNS, KC_DEL, 
		KC_BSPC, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_PSCR, KC_PGUP, KC_UP,   KC_O,    KC_P,    S(KC_GRV), KC_GRV, RESET, 
		F(1),    KC_P0,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_TRNS, KC_TRNS, 
		KC_LSFT, KC_NO,   KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_NLCK, KC_PGDN, KC_TRNS, KC_TRNS, S(KC_GRV), KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_TRNS, KC_DEL, 
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
		KC_TRNS, KC_TRNS, RGB_M_P, KC_TRNS, KC_TRNS, RGB_M_G, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, RGB_M_X, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
/* id for user defined functions */
enum function_id {
    RUSLAT,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION_TAP(RUSLAT),  // Generates Shift+Gui keys on tap or works as LCTL while holded down
    [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),

};


//Left Control key Tap (down+up) works as LShift+LGUI 
//I use LShift+LGUI for RUS/ENG keyboard layout switching
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    /*keyevent_t event = record->event;*/
    switch (id) {
        case RUSLAT:
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                    if (record->tap.interrupted) {
                        register_mods(MOD_BIT(KC_LCTRL));
                    }
                } else {
                    register_mods(MOD_BIT(KC_LCTRL));
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
			add_mods( MOD_BIT(KC_LSFT));
			add_mods( MOD_BIT(KC_LALT));
			send_keyboard_report();

			del_mods( MOD_BIT(KC_LALT));
			del_mods( MOD_BIT(KC_LSFT));
			send_keyboard_report();

			record->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_LCTRL));
                }
            }
            break;
    }
}


/* enum function_id { */
/*     SHIFT_ESC, */
/* }; */

/* const uint16_t PROGMEM fn_actions[] = { */
/*   [0]  = ACTION_FUNCTION(SHIFT_ESC), */
/* }; */

/* void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) { */
/*   static uint8_t shift_esc_shift_mask; */
/*   switch (id) { */
/*     case SHIFT_ESC: */
/*       shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK; */
/*       if (record->event.pressed) { */
/*         if (shift_esc_shift_mask) { */
/*           add_key(KC_GRV); */
/*           send_keyboard_report(); */
/*         } else { */
/*           add_key(KC_ESC); */
/*           send_keyboard_report(); */
/*         } */
/*       } else { */
/*         if (shift_esc_shift_mask) { */
/*           del_key(KC_GRV); */
/*           send_keyboard_report(); */
/*         } else { */
/*           del_key(KC_ESC); */
/*           send_keyboard_report(); */
/*         } */
/*       } */
/*       break; */
/*   } */
/* } */
