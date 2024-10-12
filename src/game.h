#pragma once

#include "common.h"
#include "state.h"
#include "renderer.h"
#include "game_detection.h"


void game_init(state_t *state);
void game_release(state_t *state);
void game_flip(state_t *state);
void game_update(state_t *state);
void game_draw(state_t *state);
