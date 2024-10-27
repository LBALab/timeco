#include <SDL3/SDL.h>
#include <stdio.h>

#include "lib/common.h"

#include "system.h"


void system_init(system_t *system, c8 *title, i32 width, i32 height, i32 bpp) {
    printf("Initializing system...\n");
    system->quit = false;
    system->title = title;
    system->width = width;
    system->height = height;
    system->bpp = bpp;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD);

    system->window = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    system->renderer = SDL_CreateRenderer(system->window, NULL);
    SDL_SetRenderLogicalPresentation(system->renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderDrawColor(system->renderer, 0, 0, 0, 255);

    SDL_UpdateWindowSurface(system->window);
}

void system_release(system_t *system) {
    SDL_DestroyTexture(system->texture);
    SDL_DestroySurface(system->surface);
    SDL_DestroyPalette(system->palette);
    SDL_DestroyRenderer(system->renderer);
    SDL_DestroyWindow(system->window);
    SDL_Quit();
}

inline void system_set_title(system_t *system, c8 *title) {
    SDL_SetWindowTitle(system->window, title);
}

inline u32 system_tick() {
    return SDL_GetTicks();
}

inline void system_delay(u32 ms) {
    SDL_Delay(ms);
}

void system_delay_events(system_t *system, u32 ms) {
    u32 start = system_tick();
    while (system_tick() - start < ms) {
        if (system->actions[ACTION_SKIP] || system->quit) {
            break;
        }
        system_events(system);
        system_delay(1);
    }
}

void system_events(system_t *system) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                system->quit = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                printf("Key down: %d\n", event.key.key);
                system->actions[event.key.key] = true;
                break;
            case SDL_EVENT_KEY_UP:
                system->actions[event.key.key] = false;
                break;
            case SDL_EVENT_MOUSE_MOTION:
                system->motion_x = event.motion.xrel;
                system->motion_y = event.motion.yrel;
                break;
            default:
                break;
        }
    }
}

void system_create_surface(system_t *system, u8 *front_buffer) {
    system->surface = SDL_CreateSurfaceFrom(
        system->width,
        system->height,
        SDL_PIXELFORMAT_INDEX8,
        front_buffer,
        system->width * system->bpp
    );
    system->palette = SDL_CreatePalette(256);
}

void system_blit(system_t *system) {
    SDL_RenderClear(system->renderer);
    if (system->texture) {
        SDL_DestroyTexture(system->texture);
    }
    system->texture = SDL_CreateTextureFromSurface(system->renderer, system->surface);
    SDL_RenderTexture(system->renderer, system->texture, NULL, NULL);
}

inline void system_flip(system_t *system) {
    SDL_RenderPresent(system->renderer);
}

void system_set_palette(system_t *system, u8 *palette) {
    for (i32 i = 0; i < 256; i++) {
        system->palette->colors[i].r = palette[i * 3 + 0];
        system->palette->colors[i].g = palette[i * 3 + 1];
        system->palette->colors[i].b = palette[i * 3 + 2];
    }
    SDL_SetSurfacePalette(system->surface, system->palette);
}
