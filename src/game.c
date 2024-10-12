#include "game.h"

#include "common.h"
#include "state.h"
#include "game_detection.h"
#include "renderer.h"




void game_init(state_t *state) {
    printf("Initializing game...\n");
}

void game_release(state_t *state) {
    memory_free(state->renderer.back_buffer);
    memory_free(state->renderer.front_buffer);
}

void game_flip(state_t *state) {
    i32 width = state->system.width;
    i32 height = state->system.height;
    i32 bpp = state->system.bpp;

    memory_copy(state->renderer.front_buffer, state->renderer.back_buffer, width * height * bpp);
}

void game_update(state_t *state) {
}

void game_draw(state_t *state) {
    // i32 width = state->system.width;
    // i32 height = state->system.height;
    // i16 bpp = state->system.bpp;
    renderer_t *renderer = &state->renderer;

    renderer_clear(renderer);
    
    //draw

    renderer_flip(renderer);
}
