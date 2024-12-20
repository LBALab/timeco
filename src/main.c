#include <SDL3/SDL.h>
#include <stdio.h>

#include "lib/common.h"

#include "system.h"
#include "system_mixer.h"
#include "state.h"
#include "game.h"
#include "game_detection.h"
#include "renderer.h"
#include "config.h"


#define ENGINE_VERSION "0.0.1"

const i32 fps = 60;
const i32 tpf = 1000 / fps;


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
    system_mixer_init(config_file.sample);
    screen_init(screen, system);
    system_create_surface(system, screen->front_buffer);

    game_init(state);

    system->timer.last_tick = system_tick();
    while(!system->quit) {
        system->timer.tick = system_tick();
        system_events(system);

        game_update(state);

        system_blit(system);
        system_flip(system);

        system->timer.last_tick = system_tick();
        if (system->timer.last_tick - system->timer.tick < tpf) {
            system_delay(tpf - (system->timer.last_tick - system->timer.tick));
        }
    }

    game_release(state);
    renderer_release(renderer);
    screen_release(screen);
    system_release(system);
    state_release(state);

    return 0;
}
