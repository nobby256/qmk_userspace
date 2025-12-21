#include QMK_KEYBOARD_H

#include "keymap_japanese.h"
#include "x_nagi_adopt.h"

bool process_kakutei(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }
  switch (keycode) {
    case JP_RPRN:
    case JP_LPRN:
    case JP_LBRC:
    case JP_RBRC:
    // case JP_COLN:
    // case JP_EXLM:
    // case JP_QUES:
    // case JP_SLSH:
    case JP_TILD:
    case KC_LT:
    case KC_GT:
      break;
    default:
      return true;
  }
  tap_code16(keycode);
  if (nagi_state()) {
    if (!(get_mods() & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))){
      tap_code(KC_ENT);
    }
  }
  return false;
}
