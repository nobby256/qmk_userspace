/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 #include QMK_KEYBOARD_H
 #include "keymap_japanese.h"

 #ifdef OS_DETECTION_ENABLE
 #   include "os_detection.h"
 #endif

 // 薙刀式 begin 1
 #include "naginata.h"
 // 薙刀式 end 1
 #include "naginata_parts.h"
 // #include "twpair_on_jis.h"

 enum custom_keycodes {
     US_KEY = NG_SAFE_RANGE,
     US2JIS,
     EDR1NGOFF,
     LWRENT,
     NG_EDIT_DELETE_TO_END,
     NG_EDIT_KAKUTEI_END,
     NG_KATAKANA,
     NG_HIRAGANA,
     NG_IME_CANCEL,
     NG_QUESTION_MARK,
     NG_EXCLAMATION_MARK,
     NG_LEFT_CORNAR_BRACKET,
     NG_RIGHT_CORNAR_BRACKET,
     NG_LEFT_PARANTHESIS,
     NG_RIGHT_PARANTHESIS,
 };

 #define SFTSPC   LSFT_T(KC_SPC)
 #define SFTZ     LSFT_T(KC_Z)
 #define SFTSLSH  LSFT_T(KC_SLSH)
 #define GUIDEL   LGUI_T(KC_DEL)
 #define ALTSELN  LALT_T(KC_SCLN)

 #define SFTNGOFF LSFT_T(NG_OFF)
 //#define CTLNGOFF LCTL_T(NG_OFF)
 #define ALTNGOFF LALT_T(NG_OFF)

 #define CTLSPC   LCTL_T(KC_SPC)
 #define CTLBS    LCTL_T(KC_BSPC)
 #define CTLTAB   LCTL_T(KC_TAB)
 #define CTLESC   LCTL_T(KC_ESC)
 #define ALTESC   LALT_T(KC_ESC)
 #define ALTTAB   LALT_T(KC_TAB)
 #define ALTSPC   LALT_T(KC_SPC)

 // Defines the keycodes used by our macros in process_record_user
 enum layer_names {
     _QWERTY,
   // 薙刀式 begin 2
     _NAGINATA, // 薙刀式入力レイヤー
   // 薙刀式 end 2
     _LOWER,
     _RAISE,
     _ADJUST,
     _LOWER2,
     _RAISE2,
     _FUNCTION,
     _EDIT_R1, //編集モード（右面1）
     _EDIT_R2, //編集モード（右面2）
     _EDIT_L1, //編集モード（左面1）
 };


enum combos {
  CMB_ALTTAB
};
// Alt+Tab
const uint16_t PROGMEM combo_alttab[] = {NG_OFF, KC_Q, COMBO_END};
// ENT
const uint16_t PROGMEM combo_ent[] = {KC_V, KC_M, COMBO_END}; //薙刀式のレイヤーではMod+ENTの為に有用
 // ADJUST(ファンクション 右面)
const uint16_t PROGMEM combo_func[] = {KC_K, KC_L, COMBO_END};
 // ADJUST(ファンクション 左面)
 const uint16_t PROGMEM combo_func2[] = {KC_S, KC_D, COMBO_END};
 // 編集モード(右面1)
const uint16_t PROGMEM combo1_edit_r1[]= {KC_D, KC_F, COMBO_END};
// 編集モード(左面1)
const uint16_t PROGMEM combo1_edit_l1[]= {KC_J, KC_K, COMBO_END};
// TAB
const uint16_t PROGMEM combo_tab[]= {KC_Q, KC_W, COMBO_END};
// ESC
const uint16_t PROGMEM combo_esc[]= {KC_O, KC_P, COMBO_END};

combo_t key_combos[] = {
  COMBO(combo_alttab, KC_NO),
  COMBO(combo_ent, KC_ENT),
  COMBO(combo_func, MO(_FUNCTION)),
  COMBO(combo_func2, MO(_FUNCTION)),
  COMBO(combo1_edit_r1, MO(_EDIT_R1)),
  COMBO(combo1_edit_l1, MO(_EDIT_L1)),
  COMBO(combo_tab, KC_TAB),
  COMBO(combo_esc, KC_ESC),
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Qwerty
  *
  * ,----------------------------------.           ,----------------------------------.
  * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
  * `-------------+-----S-+------+------|           |------+------+------+------+------'
  *               |CTL/TAB|RAISE|SPC/SFT|          |SPC/SFT|LWR/ENT|ALT/ESC|
  *               `--------------------'           `--------------------'
  */
 [_QWERTY] = LAYOUT_split_3x5_3(
//    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,   KC_I,    KC_O,   KC_P,
//    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN,
//    SFTZ,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH,
   KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y,   KC_U, KC_I,    KC_O,   KC_P,
   KC_A, KC_S, KC_D, KC_F, KC_G,      KC_H,   KC_J, KC_K,    KC_L,   KC_SCLN,
   SFTZ, LALT_T(KC_X), KC_C, KC_V, KC_B,      KC_N,   KC_M, KC_COMM, LALT_T(KC_DOT), KC_SLSH,
//         ALTESC, SFTSPC, NG_OFF,      SFTSPC, NG_SHFT2, LT(_LOWER2,KC_TAB)
           NG_OFF, SFTSPC, CTLESC,    SFTSPC, NG_SHFT2, ALTESC
),

 /* Lower
  *
  * ,----------------------------------.           ,----------------------------------.
  * | Num1 | Num2 | Num3 | Num4 | Num5 |           | Num6 | Num7 | Num8 | Num9 | Num0 |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |  TAB |   ~  | Num- | Num+ |   ^  |           |   :  | Num4 | Num5 | Num6 |  ENT |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |      |   `  | Num/ | Num* |   \  |           | Num. | Num1 | Num2 | Num3 | Num0 |
  * `-------------+------+------+------|           |------+------+------+------+------'
  *               |      |      |      |           |      |      |      |
  *               `--------------------'           `--------------------'
  */
  [_LOWER] = LAYOUT_split_3x5_3(
    // KC_P1,      KC_P2,      KC_P3,      KC_P4,      KC_P5,           KC_P6,  KC_P7,  KC_P8, KC_P9, KC_P0,
    // LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), LCTL(KC_G),      KC_BSPC,KC_P4,  KC_P5, KC_P6, JP_COLN,
    // LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),      KC_DOT, KC_P1,  KC_P2, KC_P3, KC_PSLS,
    //                            _______, _______,    _______,         KC_ESC, _______, KC_TAB
    KC_ESC,  KC_F2,   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_PAST, KC_PPLS, KC_PEQL, JP_PERC,
    KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,      KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,
    KC_LSFT, XXXXXXX, JP_CIRC, JP_GRV,  JP_YEN,     JP_COLN, KC_PMNS, KC_COMM, KC_PDOT, KC_PSLS,
                     _______, _______,  _______,    KC_BSPC,   _______, _______
 ),
 [_LOWER2] = LAYOUT_split_3x5_3(
    // KC_P1,      KC_P2,      KC_P3,      KC_P4,      KC_P5,           KC_P6,  KC_P7,  KC_P8, KC_P9, KC_P0,
    // LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), LCTL(KC_G),      KC_BSPC,KC_P4,  KC_P5, KC_P6, JP_COLN,
    // LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),      KC_DOT, KC_P1,  KC_P2, KC_P3, KC_PSLS,
    //                            _______, _______,    _______,         KC_ESC, _______, KC_TAB
    KC_F2,     KC_P7, KC_P8,  KC_P9,      JP_CIRC,   XXXXXXX, KC_PAST, KC_PPLS, KC_PEQL,  JP_PERC,
    XXXXXXX,   KC_P4, KC_P5,  KC_P6,      JP_YEN,    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, JP_COLN,
LSFT_T(KC_P0), KC_P1, KC_P2,  KC_P3,      JP_GRV,    XXXXXXX, KC_PMNS, KC_COMM, KC_PDOT,  KC_PSLS,
                      KC_ESC,KC_BSPC, LM(_RAISE2,MOD_LCTL),    _______,  _______, _______
 ),

 /* Rise
  *
  * ,----------------------------------.           ,----------------------------------.
  * GUI/DEL|   !  |   &  |   |  |   $  |           |   @  |   *  |   +  |   =  |   %  |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |  TAB |   "  |   -  |   (  |   )  |           | LEFT | DOWN |  UP  | RIGHT|   :  |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |  SFT |   '  |   #  |   {  |   }  |           | HOME | LEFT |   <  |   >  |   ?  |
  * `-------------+------+------+------|           |------+------+------+------+------'
  *               |      |      |      |           |      |      |      |
  *               `--------------------'           `--------------------'
  */
 [_RAISE] = LAYOUT_split_3x5_3(
/*
   GUIDEL,  JP_EXLM, JP_AMPR, JP_PIPE, JP_DLR,        JP_AT,   JP_ASTR, JP_PLUS, JP_EQL,  JP_PERC,
   KC_TAB,  JP_DQUO, KC_MINS, JP_LPRN, JP_RPRN,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, JP_SCLN,
   KC_LSFT, JP_QUOT, KC_HASH, JP_LCBR, JP_RCBR,       KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_QUES,
*/
   GUIDEL,  JP_EXLM, JP_AMPR, JP_PIPE, JP_DLR,        JP_AT,   JP_ASTR, JP_PLUS, JP_EQL,  JP_PERC,
   KC_ESC,  JP_DQUO, KC_PMNS, JP_LPRN, JP_RPRN,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, JP_COLN,
   KC_LSFT, JP_QUOT, JP_HASH, JP_LCBR, JP_RCBR,       KC_HOME, KC_END,  JP_LBRC, JP_RBRC, KC_PSLS,
                 _______, _______, LM(_RAISE2,MOD_LCTL),       _______, _______, _______
 ),

 [_RAISE2] = LAYOUT_split_3x5_3(
    // XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX,
    // XXXXXXX,    XXXXXXX,    LCTL(KC_D), XXXXXXX,    XXXXXXX,        LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RIGHT), XXXXXXX,
    // KC_LSFT,    LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,    XXXXXXX,    KC_D,       XXXXXXX,    XXXXXXX,        KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX,
   LSFT_T(KC_Z),KC_X,       KC_C,       KC_V,       XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                            _______,    _______,    _______,        _______, _______, _______
  ),

 /* Function
  *
  * ,----------------------------------.           ,----------------------------------.
  * |  F1  |  F2  |  F3  |  F4  |      |           |      |      |      |      |      |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |  F5  |  F6  |  F7  |  F8  |      |           |      |      |      |      |      |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |  F9 |  F10 |   F11 |  F12 | PSCR |           |      |      |      |      |      |
  * `-------------+------+------+------|           |------+------+------+------+------'
  *               |      |      |      |           |      |      |      |
  *               `--------------------'           `--------------------'
  */
 [_FUNCTION] =  LAYOUT_split_3x5_3(
   KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,   NGSW_WIN, XXXXXXX, XXXXXXX, LCTL(KC_HOME), KC_PGUP,
   KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,   NG_TAYO, XXXXXXX, XXXXXXX, LCTL(KC_END),  KC_PGDN,
   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,   NG_SHOS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     KC_LALT, KC_LSFT, KC_LCTL,   KC_LSFT, KC_LCTL, KC_LALT
 ),

 // 薙刀式 begin 3
 [_NAGINATA] = LAYOUT_split_3x5_3(
   NG_Q,     NG_W,   NG_E,    NG_R,    NG_T,          NG_Y,    NG_U,    NG_I,    NG_O,   NG_P,
   NG_A,     NG_S,   NG_D,    NG_F,    NG_G,          NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN,
   NG_Z,     NG_X,   NG_C,    NG_V,    NG_B,          NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH,
                     _______, NG_SHFT,_______,       _______, _______, _______
   ),
 // 薙刀式 end 3

 /* 編集モード1
  *
  * ,----------------------------------.           ,----------------------------------.
  * |  cut | copy | paste|      |   ・ |           |      |      |      |      |      |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * |  all | save |   ?  |   (  |   )  |           |      |      |      |      |      |
  * |------+------+------+------+------|           |------+------+------+------+------|
  * | undo | redo |   !  |   [  |   ]  |           |      |      |      |      |      |a
  * `-------------+------+------+------|           |------+------+------+------+------'
  *               |      |      |      |           |      |      |      |
  *               `--------------------'           `--------------------'
  */
  [_EDIT_R1] = LAYOUT_split_3x5_3(
    //  LCTL(KC_HOME), LCTL(KC_END), LCTL(KC_V), XXXXXXX,    KC_SLSH,        KC_HOME, NG_EDIT_DELETE_TO_END, XXXXXXX, KC_DEL,  LSFT(KC_ESC),
    //  LCTL(KC_A),    LCTL(KC_S),   KC_QUES,    KC_PGUP,    LCTL(KC_C),     KC_LEFT, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX,
    //  LCTL(KC_Z),    LCTL(KC_Y),   JP_EXLM,    KC_PGDN,    LCTL(KC_X),     KC_END,  XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX,
    // XXXXXXX,     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,        NG_EDIT_DELETE_TO_END, KC_BSPC, LGUI(KC_SLSH),         KC_DEL,     LSFT(KC_ESC),
    // XXXXXXX,     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,        KC_LEFT,               KC_DOWN, KC_UP,                 KC_RIGHT,   NG_EDIT_KAKUTEI_END,
    // KC_LSFT,     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,        KC_HOME,               KC_END,  NG_EDIT_DELETE_TO_END, LCTL(KC_U), LCTL(KC_I),
    XXXXXXX,     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,        NG_EDIT_DELETE_TO_END, KC_BSPC,  LGUI(KC_SLSH),  KC_DEL,  NG_IME_CANCEL,
    XXXXXXX,     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,        NG_EDIT_KAKUTEI_END,   KC_LEFT,  LSFT(KC_LEFT),  XXXXXXX, LCTL(KC_I),
    XXXXXXX,     XXXXXXX,    XXXXXXX,   XXXXXXX,    XXXXXXX,        KC_HOME,               KC_RIGHT, LSFT(KC_RIGHT), KC_END,  LCTL(KC_U),
                            _______,    _______,    _______,        _______,               _______, _______
  ),

  [_EDIT_R2] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,        XXXXXXX,    LCTL(KC_X), LCTL(KC_V), LCTL(KC_Y), LCTL(KC_Z),
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,        LCTL(KC_C), XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PGUP,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PGDN,
                      _______, _______,     _______,       XXXXXXX,    XXXXXXX,    XXXXXXX
  ),

  [_EDIT_L1] = LAYOUT_split_3x5_3(
    LCTL(KC_HOME), LCTL(KC_END), XXXXXXX,             XXXXXXX,                KC_SLSH,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
    XXXXXXX,       JP_TILD,      NG_QUESTION_MARK,    NG_LEFT_PARANTHESIS,    NG_RIGHT_PARANTHESIS,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
    XXXXXXX,       XXXXXXX,      NG_EXCLAMATION_MARK, NG_LEFT_CORNAR_BRACKET, NG_RIGHT_CORNAR_BRACKET,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
                                 _______,             _______,                _______,                     _______, _______, _______
  ),
 };

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFTSPC:
      return true;
    default:
      return false;
  }
}

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
  switch (combo_index) {
    case CMB_ALTTAB:
      return 1000;
    default:
      return COMBO_TERM;
  }
}
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    case CMB_ALTTAB:
      if (pressed) {
        register_mods(MOD_LALT);
        //register_code(KC_LALT);
        tap_code(KC_TAB);
      } else {
        unregister_mods(MOD_LALT);
        //unregister_code(KC_LALT);
      }
      break;
  }
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
  switch (combo_index) {
    case CMB_ALTTAB:
      switch (keycode) {
        case KC_Q:
          tap_code(KC_TAB);
          return true;
        }
  }
  return false;
}

//  layer_state_t layer_state_set_user(layer_state_t state) {
//     state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

//     //static uint32_t previous_layer = 0;
//     uint8_t current_layer = get_highest_layer(state);

//     switch (current_layer) {
//       case _CTL:
//         register_code(KC_LCTL);
//         break;
//       default:
//         unregister_code(KC_LCTL);
//         break;
//      }

//     //previous_layer = current_layer;
//     return state;
//  }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 //   static bool is_us2jis = true;
#ifdef CONSOLE_ENABLE
  const uint16_t key_timer = timer_read();  // 時間測定開始;
  uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %i, time: %u, interrupt: %i, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  bool cont = true;

  const bool pressed = record->event.pressed;
  switch (keycode) {
     // case US_KEY:
     //   if (pressed) {
     //     is_us2jis = false;
     //   }
     //   cont = false;
     //   break;
     // case US2JIS:
     //   if (pressed) {
     //     is_us2jis = true;
     //   }
     //   cont = false;
     //   break;

     // NG_*でLSFT_T()を実現しようとするコード（期待通りの効果は得れていない）
     //  case NG_Z:
     //    {
     //      static uint16_t key_pressed_time;
     //      if (pressed) {
     //        key_pressed_time = record->event.time;
     //        // process_naginata()を呼ぶ前段階では、まだregister_code相当の処理は行われていない。
     //        // KC_LSFTでprocess_naginata()を呼びだした結果、内部ではprocess_modifier()がKC_FSFTを処理する。
     //        // process_modifier()の戻り値はtrueであることから、process_naginata()終了後にregister_code()を実行すれば
     //        // process_record_user()でKC_LSFTを受け取った時の動作を疑似再現できる。
     //        process_naginata(KC_LEFT_SHIFT, record); // 戻り値派必ずtrueになる
     //        register_code(KC_LSFT);
     //      } else {
     //        process_naginata(KC_LEFT_SHIFT, record); // 戻り値派必ずtrueになる
     //        unregister_code(KC_LSFT);

     //        if (TIMER_DIFF_16(record->event.time, key_pressed_time) < TAPPING_TERM) {
     //          record->event.pressed=true;
     //          process_naginata(NG_Z, record);
     //          record->event.pressed=false;
     //          process_naginata(NG_Z, record);
     //            return false;
     //        }
     //      }
     //      return false;
     //    }
     //    break;
    case NG_EDIT_KAKUTEI_END:
      {
        if (pressed) {
          if (naginata_state()) {
            ng_edit_kakutei_end();
          } else {
            tap_code(KC_END);
          }
          return false;
       }
      }
      break;
    case NG_EDIT_DELETE_TO_END:
      {
        if (pressed) {
          ng_edit_delete_to_end();
          return false;
        }
      }
      break;
    case NG_IME_CANCEL:
      {
        if (pressed) {
          ng_ime_cancel();
          return false;
        }
      }
      break;
    case NG_QUESTION_MARK:
      {
        if (pressed) {
          if(naginata_state()){
            ng_question_mark();
          }else{
            tap_code16(LSFT(KC_SLASH));
          }
        }
        return false;
      }
      break;
    case NG_EXCLAMATION_MARK:
      {
        if (pressed) {
          if(naginata_state()){
            ng_exclamation_mark();
          }else{
            tap_code16(LSFT(JP_EXLM));
          }
          return false;
        }
      }
      break;
    case NG_LEFT_CORNAR_BRACKET:
      {
        if (pressed) {
//        tap_code16(JP_LBRC);
          tap_code16(JP_LBRC);
          tap_code16(JP_RBRC);
          if(naginata_state()){
            tap_code(KC_ENT);
          }
          ng_back_cursor();
          return false;
        }
      }
      break;
    case NG_RIGHT_CORNAR_BRACKET:
      {
        if (pressed) {
          tap_code16(JP_RBRC);
          if(naginata_state()){
            tap_code(KC_ENT);
          }
          return false;
        }
      }
      break;
    case NG_LEFT_PARANTHESIS:
      {
        if (pressed) {
//        tap_code16(JP_LPRN);
          tap_code16(JP_LPRN);
          tap_code16(JP_RPRN);
          if(naginata_state()){
            tap_code(KC_ENT);
          }
          ng_back_cursor();
          return false;
        }
      }
      break;
    case NG_RIGHT_PARANTHESIS:
      {
        if (pressed) {
          tap_code16(JP_RPRN);
          if(naginata_state()){
            tap_code(KC_ENT);
          }
          return false;
        }
      }
      break;
    case KC_HOME:
    case KC_END:
      if (get_mods() & MOD_MASK_CTRL) {
        return false; // CTLによる暴発防止
      }
      break;
    case NG_OFF:
      {
        static uint16_t key_pressed_time;
        if (pressed) {
          key_pressed_time = record->event.time;
          // process_magimata()にこのキーコードを渡す必要がある。return falseをしないこと。
          //process_naginata(KC_LCTL, record);
          //register_code(KC_LCTL);
          layer_on(_LOWER);
        } else {
          //process_naginata(KC_LCTL, record);
          //unregister_code(KC_LCTL);
          layer_off(_LOWER);
          if (TIMER_DIFF_16(record->event.time, key_pressed_time) < TAPPING_TERM) {
            naginata_off();
          }
        }
        return false;
      }
      break;
    case NG_SHFT2:
      {
        static uint16_t key_pressed_time;
        if (pressed) {
          key_pressed_time = record->event.time;
          layer_on(_RAISE);
        } else {
          layer_off(_RAISE);
          if (TIMER_DIFF_16(record->event.time, key_pressed_time) < TAPPING_TERM) {
            if(naginata_state()){ //TODO:薙刀モードが有効である事と薙刀レイヤーである事はイコールではない。薙刀レイヤー以外の場合はShift+Enterになるように修正する必要性がある
              record->event.pressed=true;
              process_naginata(NG_SHFT2, record);
              record->event.pressed=false;
              process_naginata(NG_SHFT2, record);
            } else {
              tap_code(KC_ENT);
            }
          }
        }
        return false;
      }
      break;
    case KC_SCLN: // 日本語キーボードで SHIFT + ; -> :
      {
        static bool coln_registered;
        uint8_t mod_state = get_mods();
        if (record->event.pressed) {
          if (mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            register_code(JP_COLN);
            set_mods(mod_state);
            coln_registered = true;
            return false;
          }
        } else {
          if (coln_registered) {
            del_mods(MOD_MASK_SHIFT);
            unregister_code(JP_COLN);
            set_mods(mod_state);
            coln_registered = false;
            return false;
          }
        }
      }
      break;
    case KC_SLSH: // SHIFT+/ で _
      {
        static bool sft_registered;
        static uint16_t key_pressed_time;
        if (record->event.pressed) {
          key_pressed_time = record->event.time;
          if (!(get_mods() & MOD_MASK_SHIFT)) {
            register_code(KC_LSFT);
            sft_registered=true;
          }
        } else {
          if (sft_registered) {
            unregister_code(KC_LSFT);
            sft_registered=false;
          }
          if (TIMER_DIFF_16(record->event.time, key_pressed_time) < TAPPING_TERM) {
            uint8_t mod_state = get_mods();
            if (mod_state & MOD_MASK_SHIFT) {
              del_mods(MOD_MASK_SHIFT);
              tap_code16(JP_UNDS);
              set_mods(mod_state);
            } else {
              del_mods(MOD_MASK_SHIFT);
              tap_code(KC_SLSH);
            }
          }
        }
        return false;
      }
      break;
  }

   // 薙刀式 begin 4
   if (cont) {
     cont = process_naginata(keycode, record);
   }
   // 薙刀式 end 4

   // typewriter pairing on jis keyboard
 //   if (cont && is_us2jis) {
 //     cont = twpair_on_jis(keycode, record);
 //   }

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
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);

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
