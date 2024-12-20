#pragma once

#include "lib/common.h"
#include "state.h"
#include "renderer.h"
#include "game_detection.h"


void game_init(state_t *state);
void game_release(state_t *state);

void game_introduction();
void game_image(state_t *state, u32 index, u32 delay, i32 fade_in);

void game_fps(screen_t *screen, timer_t *timer);
void game_update(state_t *state);
