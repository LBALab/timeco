#ifndef ACF_H
#define ACF_H

#include "lib/common.h"
#include "state.h"

void set_pixel(i32 x, i32 y, u8 colour);

void acf_play(state_t *state, const u8 *filename);

#endif
