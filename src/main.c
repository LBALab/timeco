#include <SDL3/SDL.h>
#include <stdio.h>

#include "common.h"
#include "state.h"
#include "game.h"
#include "game_detection.h"
#include "system.h"
#include "renderer.h"
#include "config.h"


#define ENGINE_VERSION "0.0.1"


c8 title[64];
state_t *state;


i32 main(i32 argc, c8 **argv) {
    printf("\nTimeCo v%s\n\n", ENGINE_VERSION);
    printf("(c) 2024 TimeCo team. Refer to AUTHORS file for further details.\n");
    printf("Released under the terms of the GNU GPL license version 2 (or, at your opinion, any later). See COPYING file.\n\n");
    printf("The intellectual property is currently owned by [2.21].\n");
    printf("Originaly developed by Adeline Software International in 1994.\n\n");

    config_init();

    if (config_file.debug) {
        printf("Compiled the %s at %s\n\n", __DATE__, __TIME__);
    }

    printf("Initializing...\n");
    state = memory_calloc(sizeof(state_t));
    state_init(state);
    
    printf("Detecting Game...\n");
    state->game_type = detect_game();

    system_t *system = &state->system;
    renderer_t *renderer = &state->renderer;
    screen_t *screen = &state->screen;

    system_init(system, state->system.title, 640, 480, 1);
    screen_init(screen, system);
    renderer_init(renderer, system);
    game_init(state);

    while(!system->quit) {
        system->timer.tick = system_tick();
        system_events(system);

        game_update(state);
        game_draw(state);
        game_flip(state);

        system_blit(system, screen->front_buffer);
        system_flip(system);
        system_delay(1);
    }

    game_release(state);
    renderer_release(renderer);
    screen_release(screen);
    system_release(system);
    state_release(state);

    return 0;
}
