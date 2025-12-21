#pragma once

void use_nagi(bool);
void nagi_on(void);
void nagi_off(void);
bool nagi_state(void);
bool process_nagi(uint16_t keycode, keyrecord_t *record);
bool layer_state_is_nagi(void);
void delete_to_end(void);
