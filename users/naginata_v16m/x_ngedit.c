#include QMK_KEYBOARD_H

#include "x_userkeys.h"

#include "x_ngedit.h"
#include "x_nagi_adopt.h"
#include "naginata_parts.h"

#define MODE_NONE     0
#define MODE_NG_EDIT1 1
#define MODE_NG_EDIT2 2

uint8_t ngedit_mode = MODE_NONE;

bool process_ngedit(uint16_t keycode, keyrecord_t *record){
  const bool pressed = record->event.pressed;
  if (keycode == UK_NGEDIT || keycode == UK_NGEDIT2) {
    if (pressed) {
      layer_on(_NG_EDIT);
      if (keycode == UK_NGEDIT) {
        ngedit_mode = MODE_NG_EDIT1;
      } else {
        ngedit_mode = MODE_NG_EDIT2;
        nagi_on();
      }
    } else {
      layer_off(_NG_EDIT);
      ngedit_mode = MODE_NONE;
    }
    return false;
  }
  if (ngedit_mode == MODE_NG_EDIT1) {
    if (pressed) {
      switch (keycode) {
        case UK_NGEND:
          if (nagi_state()) {
            ng_edit_kakutei_end();
          } else {
            tap_code(KC_END);
            nagi_on();
          }
          break;
        case UK_SAIHEN:
          if (nagi_state()) {
            ng_saihenkan();
          } else {
            tap_code16(G(KC_SLSH));
            nagi_on();
          }
          break;
        case UK_ESC3:
          if (nagi_state()) {
            ng_ime_cancel();
          } else {
            tap_code(KC_ESC);
          }
          break;
        default:
          return true;
          break;
      }
      return false;
    }
  } else if (ngedit_mode == MODE_NG_EDIT2) {
    if (pressed) {
      switch (keycode) {
        case KC_Q:
          ng_colon();
          break;
        case KC_A:
          ng_middle_dot();
          break;
        case KC_Z:
          ng_eof();
          break;
        case KC_W:
          ng_solidus();
          break;
        case KC_S:
          ng_right_arrow();
          break;
        case KC_X:
          ng_left_arrow();
          break;
        case KC_E:
          ng_null();
          break;
        case KC_D:
          ng_question_mark();
          break;
        case KC_C:
          ng_exclamation_mark();
          break;
        case KC_R:
          ng_corner_bracket();
          break;
        case KC_F:
          ng_parenthesis();
          break;
        case KC_V:
          ng_black_lenticular_bracket();
          break;
        case KC_T:
          ng_right_corner_bracket();
          break;
        case KC_G:
          ng_right_parenthesis();
          break;
        case KC_B:
          ng_right_black_lenticular_bracket();
          break;
      }
    }
    return false;
  }
  return true;
}
