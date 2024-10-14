#include <SDL3/SDL.h>
#include <stdio.h>

#include "system.h"
#include "common.h"


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

    system->texture = SDL_CreateTexture(
        system->renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STATIC,
        width,
        height
    );

    SDL_UpdateWindowSurface(system->window);
}

void system_release(system_t *system) {
    SDL_DestroyTexture(system->texture);
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

void system_blit(system_t *system, u8 *front_buffer) {
    SDL_RenderClear(system->renderer);
    SDL_UpdateTexture(system->texture, NULL, front_buffer, system->width * system->bpp);
    SDL_RenderTexture(system->renderer, system->texture, NULL, NULL);
}

inline void system_flip(system_t *system) {
    SDL_RenderPresent(system->renderer);
}

void system_set_palette(system_t *system, u8 *palette) {
    // SDL_Palette *pal = SDL_AllocPalette(256);
    // SDL_SetPaletteColors(pal, (SDL_Color *)palette, 0, 256);
    // SDL_SetSurfacePalette(system->surface, pal);
}
