#include QMK_KEYBOARD_H

#include "x_userkeys.h"

#include "x_nagi_adopt.h"

enum combos {
  CMB_ENT,
  CMB_DEL,
  CMB_ESC,
  CMB_TAB,
  CMB_NG_EDIT_LAYER,
  CMB_NG_EDIT2_LAYER,
//  CMB_NUM_LAYER,
  CMB_NG_ON,
};

const uint16_t PROGMEM combo_ent[]     = {KC_V, KC_M, COMBO_END};     // Enter
const uint16_t PROGMEM combo_ng_edit[] = {KC_D, KC_F, COMBO_END};     // _NG_EDIT
const uint16_t PROGMEM combo_ng_edit2[]= {KC_J, KC_K, COMBO_END};     // _NG_EDIT
const uint16_t PROGMEM combo_del[]     = {KC_U, KC_R, COMBO_END};     // UK_DEL
// const uint16_t PROGMEM combo_esc[]     = {KC_O, KC_P, COMBO_END};     // ESC
// const uint16_t PROGMEM combo_tab[]     = {KC_Q, KC_W, COMBO_END};     // TAB
const uint16_t PROGMEM combo_esc[]     = {KC_Q, KC_W, COMBO_END};     // ESC
const uint16_t PROGMEM combo_tab[]     = {KC_A, KC_S, COMBO_END};     // TAB
//const uint16_t PROGMEM combo_num[]     = {KC_F, KC_G, COMBO_END};     // NUM
const uint16_t PROGMEM combo_nagi[]    = {KC_H, KC_J, COMBO_END};     // NG_ON Shift+Hのget_hold_on_other_key_pressの為に必要

combo_t key_combos[] = {
  COMBO(combo_ent,     KC_ENT),
  COMBO(combo_del,     KC_NO),
  COMBO(combo_esc,     KC_ESC),
  COMBO(combo_tab,     KC_TAB),
  COMBO(combo_ng_edit, UK_NGEDIT),
  COMBO(combo_ng_edit2,UK_NGEDIT2),
//  COMBO(combo_num,     UK_NUM),
  COMBO(combo_nagi,    NG_ON),
};

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
  switch (combo_index) {
    case CMB_ENT:
    case CMB_DEL:
    case CMB_NG_EDIT_LAYER:
      return COMBO_TERM * 1.5;
    default:
      return COMBO_TERM;
  }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
      case CMB_ENT:
      //case CMB_NG_EDIT_LAYER:
      case CMB_NG_EDIT2_LAYER:
      case CMB_NG_ON: // 薙刀式の時は無効にしないと「じゃ」とかの入力に困る
//      case CMB_NG_ON:
        if (layer_state_is_nagi()) {
          return false;
        }
        break;
      // case CMB_NUM_LAYER:
      //   if (layer_state_is_nagi()) {
      //     return true;
      //   }
      //   uint8_t current_layer = get_highest_layer(layer_state);
      //   if (current_layer == 0) {
      //     return true;
      //   }
      //   return false;
      //   break;
    }
    return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    case CMB_DEL:
      if (pressed) {
        delete_to_end();
      }
      break;
  }
}
