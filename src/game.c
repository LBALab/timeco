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
    system_set_palette(&state->system, state->screen.palette);
}

void game_release(state_t *state) {
}

// u8 colour = 0;
void game_fps(screen_t *screen, timer_t *timer) {
    timer->frame_count++;
    if (timer->tick - timer->last_tick >= 1000) {
        sprintf(fps_text, "FPS: %d", timer->frame_count);
        timer->frame_count = 0;
        timer->last_tick = timer->tick;
        // colour = (colour + 1) % 16;
        debug_set_colour(5);
    }
    debug_draw_text(screen->front_buffer, 10, 10, fps_text);
}

void game_update(state_t *state) {
    
}


void game_draw(state_t *state) {
    screen_clear(&state->screen);
    screen_flip(&state->screen);
    game_fps(&state->screen, &state->system.timer);
    // renderer_t *renderer = &state->renderer;
    // renderer_clear(renderer);
    // //draw
    // renderer_flip(renderer, state->screen.back_buffer);
}
