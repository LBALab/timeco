#include "game.h"

#include "common.h"
#include "state.h"
#include "game_detection.h"
#include "renderer.h"
#include "screen.h"
#include "hqr.h"
#include "lib/screen/debug_font.h"


#define HQR_PALETTE_MENU 5

char fps_text[64];




void game_init(state_t *state) {
    printf("Initializing game...\n");

    if(!hqr_get_entry(state->screen.palette, "RESSOURC.HQR", HQR_PALETTE_MENU)) {
		printf("Error: Couldn't load palette\n");
	}
}

void game_release(state_t *state) {
}

void game_fps(screen_t *screen, timer_t *timer) {
    timer->frame_count++;
    if (timer->tick - timer->last_tick >= 1000) {
        sprintf(fps_text, "FPS: %d", timer->frame_count);
        draw_text(screen->back_buffer, 0, 0, fps_text);
        timer->frame_count = 0;
        timer->last_tick = timer->tick;
    }
}

void game_flip(state_t *state) {
    memory_copy(state->screen.front_buffer, state->screen.back_buffer, state->system.width * state->system.height * state->system.bpp);
}

void game_update(state_t *state) {
    
}


void game_draw(state_t *state) {
    game_fps(&state->screen, &state->system.timer);
    // renderer_t *renderer = &state->renderer;
    // renderer_clear(renderer);
    // //draw
    // renderer_flip(renderer, state->screen.back_buffer);
}
