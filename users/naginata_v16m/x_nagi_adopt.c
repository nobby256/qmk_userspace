#include QMK_KEYBOARD_H

#include "x_userkeys.h"

#include "x_nagi_adopt.h"
#include "naginata.h"
#include "naginata_parts.h"

bool enable_nagi = true;
bool ime_state = false;

void nagi_on() {
  if (enable_nagi) {
    naginata_on();
  } else {
    tap_code(KC_LANGUAGE_1);
  }
  ime_state = true;
}
void nagi_off() {
  if (enable_nagi) {
    naginata_off();
  } else {
    tap_code(KC_LANGUAGE_2);
  }
  ime_state = false;
}

bool nagi_state(void) {
  if (enable_nagi) {
    return naginata_state();
  } else {
    return ime_state;
  }
}

void use_nagi(bool enable) {
  enable_nagi = enable;
  if (enable) {
    nagi_on();
  } else {
    nagi_off();
  }
}

bool process_nagi(uint16_t keycode, keyrecord_t *record) {
  bool pressed = record->event.pressed;
  if (pressed) {
    switch (keycode) {
      case UK_NGON:
        use_nagi(true);
        return false;
      case UK_NGOFF:
        use_nagi(false);
        return false;
      case KC_LANGUAGE_1:
          // if (ime_state()) {
          //   //tap_code16(LCTL(KC_M)); // IMEがONなら確定
          //   ng_ime_complete(); // IMEがONなら確定
          // } else {
          //   set_ime(true); // IMEがOFFならIME ON
          // }
          nagi_on();
        return false;
      case KC_LANGUAGE_2:
        nagi_off();
        return false;
      case LALT(KC_GRV):
        if (nagi_state()) {
          nagi_off();
        } else {
          nagi_on();
        }
        return false;
    }
  }
  if (enable_nagi) {
    return process_naginata(keycode, record);
  }
  return true;
}

bool layer_state_is_nagi(void) {
  if (enable_nagi) {
    uint8_t naginaga_layer = get_naginata_layer();
    uint8_t current_layer = get_highest_layer(layer_state);
    return naginaga_layer == current_layer;
  } else {
    return false;
  }
}

void delete_to_end(void) {
  if (enable_nagi) {
    ng_edit_delete_to_end();
  } else {
    add_mods(MOD_BIT(KC_LEFT_SHIFT));
    tap_code(KC_END);
    del_mods(MOD_BIT(KC_LEFT_SHIFT));
    tap_code(KC_BACKSPACE);
  }
}
