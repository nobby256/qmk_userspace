#include QMK_KEYBOARD_H

#include "x_alttab.h"

#include "x_nagi_adopt.h"

static bool alttab_mode;
static bool alttab_shift;

bool process_alttab(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // Key Down
    if (!alttab_mode) {
      if (keycode == KC_Q) {
        if (get_mods() & MOD_MASK_CTRL){
          alttab_mode = true;
          alttab_shift = false;
          unregister_mods(MOD_LCTL);
          wait_ms(30);
          register_mods(MOD_LALT);
          wait_ms(30);
          tap_code(KC_TAB);
          return false;
        }
      }
    } else {
      if (keycode == KC_Q) {
        if (alttab_shift) {
          tap_code16(LSFT(KC_TAB));
        } else {
          tap_code(KC_TAB);
        }
        return false;
      } else if (keycode == KC_Z) {
        alttab_shift = true;
        return false;
      }
    }
  } else {
    // Key Up
    if (alttab_mode) {
      if (keycode == KC_Z) {
        alttab_shift = false;
        return false;
      } else if (keycode == KC_LCTL) {
        alttab_mode = false;
        unregister_mods(MOD_LALT);
        process_nagi(KC_LALT, record);
        return false;
      }
    }
  }
  return true;
}
