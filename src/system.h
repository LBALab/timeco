#pragma once

#include <SDL3/SDL.h>

#include "common.h"

typedef struct {
    u32 tick;
    u32 last_tick;
    u32 frame_count;
} timer_t;

typedef struct {
    b8 quit;
    i32 width;
    i32 height;
    i16 bpp;
    c8 *title;
    timer_t timer;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    i32 actions[256];
    f32 motion_x;
    f32 motion_y;
} system_t;


void system_init(system_t *system, c8 *game_title, i32 width, i32 height, i32 bpp);
void system_events(system_t *system);
u32 system_tick();
void system_delay();
void system_set_title(system_t *system, c8 *title);
void system_blit(system_t *system, u8 *front_buffer);
void system_flip(system_t *system);
void system_release(system_t *system);
