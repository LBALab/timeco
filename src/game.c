#include "game.h"

#include "lib/common.h"
#include "lib/screen.h"
#include "lib/debug_font.h"
#include "lib/hqr.h"
#include "state.h"
#include "game_detection.h"
#include "renderer.h"


#define HQR_PALETTE_MENU 5

char fps_text[64];
u32 fps_elapsed = 0;
f32 fps_elapsed_delta = 0;



void game_init(state_t *state) {
    printf("Initializing game...\n");
    debug_set_colour(200); // 15

    // if(!hqr_get_entry(state->screen.palette, "RESSOURC.HQR", HQR_PALETTE_MENU)) {
	// 	printf("Error: Couldn't load palette\n");
	// }
    // system_set_palette(&state->system, state->screen.palette);

    // activision.acf logo if US
    screen_image(&state->screen, &state->system, 34, 6000, FALSE);
    screen_image(&state->screen, &state->system, 38, 6000, TRUE);
    // Virgin if JP or ASIA

    // then menu > new game > then timewrap acf

    screen_image(&state->screen, &state->system, 42, 0, TRUE);
}

void game_release(state_t *state) {
}

void game_fps(screen_t *screen, timer_t *timer) {
    if (fps_elapsed < 500) {
        fps_elapsed += timer->tick - timer->last_tick;
    } else {
        fps_elapsed_delta = (f32)(timer->tick - timer->last_tick) / 1000.0f;
        fps_elapsed = 0;
    }
    sprintf(fps_text, "FPS: %d", (i32)(1.0f / fps_elapsed_delta));
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
