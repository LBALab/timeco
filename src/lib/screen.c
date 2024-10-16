#include <math.h>

#include "screen.h"
#include "common.h"
#include "hqr.h"

#include "../system.h"
#include "../config.h"


#define NUM_COLOURS 256


void screen_init(screen_t *screen, system_t *system) {
    printf("Initializing screen...\n");
    screen->width = system->width;
    screen->height = system->height;
    screen->bpp = system->bpp;

    screen->back_buffer = (u8 *)memory_alloc(screen->width * screen->height * screen->bpp * sizeof(u8));
    screen->front_buffer = (u8 *)memory_alloc(screen->width * screen->height * screen->bpp * sizeof(u8));
}

void screen_release(screen_t *screen) {
    memory_free(screen->back_buffer);
    memory_free(screen->front_buffer);
}

inline void screen_flip(screen_t *screen) {
    memory_copy(screen->front_buffer, screen->back_buffer, screen->width * screen->height * screen->bpp);
}

inline void screen_clear_back_buffer(screen_t *screen) {
    memset(screen->back_buffer, 0, screen->width * screen->height * screen->bpp * sizeof(u8));
}

inline void screen_clear(screen_t *screen) {
    memset(screen->front_buffer, 0, screen->width * screen->height * screen->bpp * sizeof(u8));
}

void screen_image(screen_t *screen, system_t *system, u32 index, u32 delay, i32 fade_in) {
    if (!hqr_get_entry(screen->palette, "RESSOURC.HQR", index)) {
        printf("Error: Couldn't load palette %d\n", index);
    }
    if (!hqr_get_entry(screen->back_buffer, "RESSOURC.HQR", index + 3)) { // +3 highest quality
        printf("Error: Couldn't load image %d\n", index);
    }

    screen_flip(screen);
    if (fade_in) {
        screen_fade_to_pal(system, screen->palette);
    } else {
        system_set_palette(system, screen->palette);
    }
    system_blit(system);
    system_flip(system);
    
    if (delay) {
        system_delay_events(system, (config_file.debug) ? 750 : delay);
        screen_fade_to_black(system, screen->palette);
        screen_clear_back_buffer(screen);
    }
}

void screen_fade_to_pal(system_t *system, u8 *palette) {
    i32 i = 100;
    for (i = 0; i <= 100; i += 3) {
        screen_adjust_palette(system, 0, 0, 0, (u8 *) palette, i);
        system_delay(20);
    }
}

void screen_fade_to_black(system_t *system, u8 *palette) {
    i32 i = 0;
    for (i = 100; i >= 0; i -= 3) {
        screen_adjust_palette(system, 0, 0, 0, (u8 *) palette, i);
        system_delay(20);
    }
}

i32 screen_cross_dot(i32 modifier, i32 color, i32 param, i32 intensity) {
    if (!param) {
        return color;
    }
    return (((color - modifier) * intensity) / param) + modifier;
}

void screen_adjust_palette(system_t *system, u8 R, u8 G, u8 B, u8 * palette, i32 intensity) {
    u8 localPalette[NUM_COLOURS*3];
    u8 *newR;
    u8 *newG;
    u8 *newB;

    i32 local;
    i32 counter = 0;
    i32 i;

    local = intensity;

    newR = &localPalette[0];
    newG = &localPalette[1];
    newB = &localPalette[2];

    for (i = 0; i < NUM_COLOURS; i++) {
        *newR = screen_cross_dot(R, palette[counter + 0], 100, local);
        *newG = screen_cross_dot(G, palette[counter + 1], 100, local);
        *newB = screen_cross_dot(B, palette[counter + 2], 100, local);
        newR += 3;
        newG += 3;
        newB += 3;
        counter += 3;
    }

    system_set_palette(system, localPalette);

    system_blit(system);
    system_flip(system);
}
