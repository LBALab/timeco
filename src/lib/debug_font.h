#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H

#include "common.h"

void debug_set_colour(u8 colour);
void debug_draw_text(u8* screen_buffer, i32 x, i32 y, char *str);

#endif
