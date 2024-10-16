#pragma once

#include "screen.h"
#include "common.h"
#include "../system.h"
#include "../pixel_colour.h"


typedef struct {
    i32 width;
    i32 height;
    i16 bpp;
    u8 *back_buffer;
    u8 *front_buffer;
    u8 palette[256 * 3];
} screen_t;


void screen_init(screen_t *screen, system_t *system);
void screen_release(screen_t *screen);

void screen_flip(screen_t *screen);
void screen_clear(screen_t *screen);
void screen_clear_back_buffer(screen_t *screen);

void screen_image(screen_t *screen, system_t *system, u32 index, u32 delay, i32 fade_in);

void screen_fade_to_pal(system_t *system, u8 *palette);
void screen_fade_to_black(system_t *system, u8 *palette);
i32 screen_cross_dot(i32 modifier, i32 color, i32 param, i32 intensity);
void screen_adjust_palette(system_t *system, u8 R, u8 G, u8 B, u8 * palette, i32 intensity);
