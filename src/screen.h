#pragma once

#include "screen.h"
#include "common.h"
#include "system.h"
#include "pixel_colour.h"


typedef struct {
    i32 width;
    i32 height;
    i16 bpp;
    u8 *back_buffer;
    u8 *front_buffer;
} screen_t;


void screen_init(screen_t *screen, system_t *system);
void screen_release(screen_t *screen);

void screen_flip(screen_t *screen);
void screen_clear(screen_t *screen);
