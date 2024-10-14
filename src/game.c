#include "game.h"

#include "common.h"
#include "state.h"
#include "game_detection.h"
#include "renderer.h"




void game_init(state_t *state) {
    printf("Initializing game...\n");

    
}

void game_release(state_t *state) {
}

void game_flip(state_t *state) {
    memory_copy(state->renderer.front_buffer, state->renderer.back_buffer, state->system.width * state->system.height * state->system.bpp);
}

void game_update(state_t *state) {
}

void game_draw(state_t *state) {
    // renderer_t *renderer = &state->renderer;

    // renderer_clear(renderer);
    
    // //draw

    // renderer_flip(renderer);
}
