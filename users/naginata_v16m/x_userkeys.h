#pragma once

#include "keymap_japanese.h"
#include "naginata.h"
#include "x_combo.h"

enum custom_keycodes {
  UK_NGEND = NG_SAFE_RANGE,
  UK_SAIHEN,    // 再変換
  UK_ESC3,      // ESCx3
  UK_NGON,      // 薙刀式の有効化
  UK_NGOFF,     // 薙刀式の無効化
  UK_KUTN,      //「、」
  UK_TOTN,      //「。」
  UK_NAMI,      //「～」
  UK_NGEDIT,    // 薙刀式編集レイヤー
  UK_NGEDIT2,   // 薙刀式編集レイヤー
  UK_NUM        // 数字レイヤー
};


#define LT_UPPR   TL_UPPR
#define LT_LOWR   TL_LOWR
#define LT_UPPR1  LT(TL_UPPR, NG_ON)
#define LT_LOWR1  LT(TL_LOWR, NG_ON)
#define LT_UPPR2  LT(TL_UPPR, NG_OFF)
#define LT_LOWR2  LT(TL_LOWR, NG_OFF)

#define LT_T      LT(_FUNC,KC_T)
#define LT_Y      LT(_FUNC,KC_Y)

#define LST_SPC   LSFT_T(KC_SPC)  // _QWERTY
#define RST_SPC   RSFT_T(KC_SPC)  // _QWERTY
#define RST_ENT   RSFT_T(KC_ENT)  // _LOWER
#define CT_SLSH   RCTL_T(JP_SLSH) // _QWERTY
#define CT_MINS   RCTL_T(JP_MINS) // _QWERTY
#define CT_NGSLSH RCTL_T(NG_SLSH) // _QWERTY
#define CT_DOT    LCTL_T(KC_DOT)  // _LOWER

#define ST_SLSH   RSFT_T(JP_SLSH) // _QWERTY
#define ST_NGSLSH RSFT_T(NG_SLSH) // _QWERTY
#define ST_NGON   LSFT_T(NG_ON)   // _QWERTY
#define AT_NGON   LALT_T(NG_ON)   // _QWERTY

#define ST_RPRN   LSFT_T(JP_RPRN) // _RAISE
#define CT_LPRN   LCTL_T(JP_LPRN) // _RAISE
#define CT_AMPR   LCTL_T(JP_AMPR) // _RAISE
#define ST_LPRN   LSFT_T(JP_LPRN) // _RAISE

#define C_HOME    C(KC_HOME)
#define C_END     C(KC_END)

#define AS_F      A(S(KC_F))
#define AS_O      A(S(KC_O))

// Defines the keycodes used by our macros in process_record_user
enum layer_names {
  _QWERTY,
  _COLMAK,
  _NAGINATA, // 薙刀式入力レイヤー
  _LOWER,
  _RAISE,
  _ADJUST,
  _NG_EDIT,
  _NUM,
  _FUNC,
};
