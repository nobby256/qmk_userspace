#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

#include "x_userkeys.h"

#include "naginata.h"
#include "naginata_parts.h"
#include "x_nagi_adopt.h"
#include "x_alttab.h"
#include "x_layer.h"
#include "x_combo.h"
#include "x_kakutei.h"
#include "x_zenkaku.h"
#include "x_ngedit.h"

//holdキーをtapキーよりも先にリリースするとタップ扱い
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // 以下、naginata_offキーがpermissive_holdになっていることは重要。
    // naginata_off(TAP)→SHIFT(HOLD)を高速に入力してかな入力から大文字英語に切り替えるためにはhold_on_other_key_pressではダメ
    case LT_UPPR:
    case LT_UPPR1:
    case LT_UPPR2:
    case LT_LOWR:
    case LT_LOWR1:
    case LT_LOWR2:
      return true;
    default:
      return false;
  }
}
//holdキーをtapキーよりも先にリリースしてもホールド扱い
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CT_NGSLSH: //Ctrl+CでCtrlを先に放す癖がある
    case CT_SLSH:   //Ctrl+CでCtrlを先に放す癖がある
    // 高速に大文字/小文字交じりの英単語を入力するには、LST_SPC/RST_SPCをhold_on_other_key_pressにする必要がある
    case LST_SPC:   //%NG_ONをCOMBOにすることもセットにしなければ効果はない
    case RST_SPC:
    case RST_ENT:
      return true;
     default:
      return false;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  const uint16_t key_timer = timer_read();  // 時間測定開始;
  uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %i, time: %u, interrupt: %i, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  bool cont = true;

  const bool pressed = record->event.pressed;
  if(record->tap.count) {
    // tap
    switch (keycode) {
      case ST_RPRN: // _RAISE
        keycode = JP_RPRN;
        break;
      case CT_AMPR: //_RAISE
        if (pressed) {
          register_code16(JP_AMPR);
        } else {
          unregister_code16(JP_AMPR);
        }
        return false;
        break;
      case CT_LPRN: // _RAISE
      case ST_LPRN: // _RAISE
        keycode = JP_LPRN;
        break;
      case CT_MINS: //_QERTY
        {
          uint8_t mod_state = get_mods();
          if (mod_state & MOD_MASK_SHIFT) {
            if (pressed) {
              tap_code16(JP_UNDS);
              return false;
            } else {
              return true;
            }
          } else {
            keycode = JP_MINS;
          }
        }
        break;
      case CT_NGSLSH: //_NAGINATA
      case ST_NGSLSH: //_NAGINATA
        keycode = NG_SLSH;
        break;
      case CT_SLSH:
      case ST_SLSH:
        {
          uint8_t mod_state = get_mods();
          if (mod_state & MOD_MASK_SHIFT) {
            if (pressed) {
              tap_code16(JP_UNDS);
              return false;
            } else {
              return true;
            }
          } else {
            keycode = JP_SLSH;
          }
        }
        break;
      // case LST_SPC:
      // case RST_SPC:
      //   {
      //     uint8_t mod_state = get_mods();
      //     if (mod_state & MOD_MASK_SHIFT) {
      //       if (pressed) {
      //         del_mods(MOD_MASK_SHIFT);
      //         //tap_code(KC_BSPC);
      //         tap_code(KC_ENT);
      //         set_mods(mod_state);
      //       }
      //       return false;
      //     }
      //   }
      //   break;
      case ST_NGON: //_QWERTY
      case AT_NGON: //_QWERTY
        keycode = NG_ON;
        break;
      case LT_T:
        keycode = KC_T;
        break;
      case LT_Y:
        keycode = KC_Y;
        break;
    }
  }

  if (cont) {
    cont = process_ngedit(keycode, record);
  }

  switch (keycode) {
    case KC_HOME:
    case KC_END:
      // CTRL押下中でも行頭、行末への移動を有効にする
      uint8_t mod_state = get_mods();
      if (mod_state & MOD_MASK_CTRL) {
        if (pressed) {
          del_mods(MOD_MASK_CTRL);
          tap_code(keycode);
          set_mods(mod_state);
          return false;
        } else {
          return true;
        }
      }
      break;
    case KC_SCLN:
      {
        uint8_t mod_state = get_mods();
        if (mod_state & MOD_MASK_SHIFT) {
          if (pressed) {
            // // JP_COLNは非シフトキーなのでdel_modsでシフトを解除しないと`*`が出力されてしまう
            del_mods(MOD_MASK_SHIFT);
            tap_code16(JP_COLN);
            // tap_code(JP_MINS);
            set_mods(mod_state);
            return false;
          } else {
            return true;
          }
        }
      }
      break;
    // case UK_NGEDIT:
    //   if (pressed) {
    //     layer_on(_NG_EDIT);
    //   } else {
    //     layer_off(_NG_EDIT);
    //   }
    //   return false;
    //   break;
    // case UK_NGEND:
    //   if (pressed) {
    //     tap_code(KC_END);
    //     nagi_on();
    //     return false;
    //   }
    case UK_NUM:
    case LT_T:
    case LT_Y:
      static bool prev_nagi_state = false;
      if (pressed) {
        prev_nagi_state = nagi_state();
        if (prev_nagi_state) {
          nagi_off();
        }
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
        if (prev_nagi_state) {
          nagi_on();
          prev_nagi_state = false;
        }
      }
      return false;
      break;
  }

  if (cont) {
    cont = process_alttab(keycode, record);
  }

  if (cont) {
    cont = process_layer(keycode, record);
  }

  if (cont) {
    cont = process_zenkaku(keycode, record);
  }

  if (cont) {
    cont = process_kakutei(keycode, record);
  }

  if (cont) {
    cont = process_nagi(keycode, record);
  }

#ifdef CONSOLE_ENABLE
  uprintf("%c%ums\n", pressed ? '*' : ' ', timer_elapsed(key_timer));  // 経過時間表示
#endif
  return cont;
}

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  // debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
#endif

// 全ての QMK 処理の最後に、次の繰り返しを開始する前に呼び出される関数
void housekeeping_task_user(void) {
  // 薙刀式 begin 5
  // 後置シフト待ち処理
  kouchi_shift_loop();
  // 薙刀式 end 5
}

void matrix_init_user(void) {
  // 薙刀式 begin 6
  //uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  uint16_t ngonkeys[] = {KC_NO, KC_NO}; // Shift+Hを高速に入力する為にH+JはCOMBOにする必要がある（Shiftを先に話す癖がある）
  //uint16_t ngoffkeys[] = {KC_NO, KC_NO};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  naginata_off();

  // 自動でOSによってレイヤーや薙刀式の設定を切り替える
#ifdef OS_DETECTION_ENABLE
  wait_ms(400);
    switch (detected_host_os()) {
      case OS_WINDOWS:
        switchOS(NG_WIN);
        break;
      case OS_MACOS:
      case OS_IOS:
        switchOS(NG_MAC);
        break;
      case OS_LINUX:
        switchOS(NG_LINUX);
        break;
      default:
        break;
    }
#endif
  // 薙刀式 end 6
}
