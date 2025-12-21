#include QMK_KEYBOARD_H

#include "x_userkeys.h"

#include "x_zenkaku.h"
#include "x_nagi_adopt.h"

bool tap_zenkaku_kigou(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) {
    return false;
  }
  bool state = nagi_state();
  if (!state) {
    nagi_on();
  }
  tap_code16(keycode);
  tap_code(KC_ENT);
  if (!state) {
    nagi_off();
  }
  return false;
}

//強制的にIMEをONにして「、」を出力
bool tap_kuten(keyrecord_t *record) {
  uint8_t mods = get_mods();
  del_mods(MOD_MASK_SHIFT);
  bool cont = tap_zenkaku_kigou(JP_COMM, record);
  set_mods(mods);
  return cont;
}
//強制的にIMEをONにして「。」を出力
bool tap_touten(keyrecord_t *record) {
  uint8_t mods = get_mods();
  del_mods(MOD_MASK_SHIFT);
  bool cont = tap_zenkaku_kigou(JP_DOT, record);
  set_mods(mods);
  return cont;
}
//強制的にIMEをONにして「～」を出力
bool tap_nami(keyrecord_t *record) {
  return tap_zenkaku_kigou(JP_TILD, record);
}
bool press_rshift_lshift(void) {
  uint8_t mods = get_mods(); // 必要なら weak/oneshot も OR する
  bool lshift = mods & MOD_BIT(KC_LSFT);
  bool rshift = mods & MOD_BIT(KC_RSFT);
  return (lshift && rshift);
}
bool process_zenkaku(uint16_t keycode, keyrecord_t *record) {
  bool cont = true;
  switch (keycode) {
    case UK_KUTN:
      cont = tap_kuten(record);
      break;
    case UK_TOTN:
      cont = tap_touten(record);
      break;
    case UK_NAMI:
      cont = tap_nami(record);
      break;
    case KC_M:
      if (press_rshift_lshift()) {
        cont = tap_touten(record);
      }
      break;
    case KC_V:
      if (press_rshift_lshift()) {
        cont = tap_kuten(record);
      }
      break;
  }
  return cont;
}
