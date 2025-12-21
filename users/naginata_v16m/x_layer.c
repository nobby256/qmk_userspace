#include QMK_KEYBOARD_H

#include "x_userkeys.h"
#include "naginata.h"

#include "x_layer.h"
#include "x_nagi_adopt.h"

bool process_layer(uint16_t keycode, keyrecord_t *record){
  switch(keycode) {
    case NG_ON:
    case NG_OFF:
      break;
    case LT_UPPR:
      keycode = TL_UPPR;
      break;
    case LT_LOWR:
      keycode = TL_LOWR;
      break;
    case LT_UPPR1:
      keycode = record->tap.count ? NG_ON : TL_UPPR;
      break;
    case LT_LOWR1:
      keycode = record->tap.count ? NG_ON : TL_LOWR;
      break;
    case LT_UPPR2:
      keycode = record->tap.count ? NG_OFF : TL_UPPR;
      break;
    case LT_LOWR2:
      keycode = record->tap.count ? NG_OFF : TL_LOWR;
      break;
    default:
      return true;
  }

  uint8_t lower_layer = get_tri_layer_lower_layer();
  uint8_t upper_layer = get_tri_layer_upper_layer();
  uint8_t adjust_layer = get_tri_layer_adjust_layer();

  if (keycode == NG_ON) {
    if (get_mods() & MOD_MASK_CSAG) {
      return true;
    } else {
      nagi_on();
    }
  } else if (keycode == NG_OFF) {
    if (get_mods() & MOD_MASK_CSAG) {
      return true;
    } else {
      nagi_off();
    }
  } else {
    uint8_t layer = keycode == TL_UPPR ? upper_layer : lower_layer;
    if (record->event.pressed) {
      layer_on(layer);
    } else {
      layer_off(layer);
    }
    update_tri_layer(lower_layer, upper_layer, adjust_layer);
  }
  return false;
}
