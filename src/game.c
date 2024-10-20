#include "game.h"

#include "lib/common.h"
#include "lib/screen.h"
#include "lib/debug_font.h"
#include "lib/hqr.h"
#include "state.h"
#include "game_detection.h"
#include "renderer.h"
#include "sample.h"


#define HQR_PALETTE_MENU 5
#define HQR_RESSOURCE "RESSOURC.HQR"


char fps_text[64];
u32 fps_elapsed = 0;
f32 fps_elapsed_delta = 0;



void game_init(state_t *state) {
    printf("Initializing game...\n");
    debug_set_colour(200); // 15

    sample_init();
    renderer_init(&state->renderer, &state->system);

    game_introduction();
}

void game_image(state_t *state, u32 index, u32 delay, i32 fade_in) {
    if (!hqr_get_entry(state->screen.palette, HQR_RESSOURCE, index)) {
        printf("Error: Couldn't load palette %d\n", index);
    }
    if (!hqr_get_entry(state->screen.back_buffer, HQR_RESSOURCE, index + 3)) { // +3 highest quality
        printf("Error: Couldn't load image %d\n", index);
    }

    screen_image(&state->screen, &state->system, index, delay, fade_in);
}

void game_introduction() {
    // if(!hqr_get_entry(state->screen.palette, "RESSOURC.HQR", HQR_PALETTE_MENU)) {
	// 	printf("Error: Couldn't load palette\n");
	// }
    // system_set_palette(&state->system, state->screen.palette);

    // activision.acf logo if US
    
    sample_play(3, 22050, 0, 0);
    game_image(state, 34, 6000, FALSE);

    game_image(state, 38, 6000, TRUE);
    // Virgin if JP or ASIA

    // then menu > new game > then timewrap acf

    game_image(state, 42, 0, TRUE);
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
    screen_clear(&state->screen);
    screen_flip(&state->screen);
    game_fps(&state->screen, &state->system.timer);
    // renderer_t *renderer = &state->renderer;
    // renderer_clear(renderer);
    // //draw
    // renderer_flip(renderer, state->screen.back_buffer);
}
