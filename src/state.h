#pragma once

#include "lib/common.h"
#include "lib/screen.h"

#include "system.h"
#include "renderer.h"
#include "game_detection.h"


typedef struct {
    system_t system;
    screen_t screen;
    renderer_t renderer;
    game_type_e game_type;
} state_t;

extern state_t *state;


void state_init(state_t *state);
void state_release(state_t *state);
