#include <math.h>

#include "screen.h"
#include "common.h"
#include "state.h"
#include "hqr.h"


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

inline void screen_clear(screen_t *screen) {
    memset(screen->front_buffer, 0, screen->width * screen->height * screen->bpp * sizeof(u8));
}

void screen_image(screen_t *screen, u32 index, u32 delay, i32 fade_in) {
    if (!hqr_get_entry(screen->palette, "RESSOURC.HQR", index)) {
        printf("Error: Couldn't load palette %d\n", index);
    }
    if (!hqr_get_entry(screen->back_buffer, "RESSOURC.HQR", index + 3)) { // +3 High Quality Resource 640x480
        printf("Error: Couldn't load image %d\n", index);
    }

    if (fade_in) {
        // fade to pal
    } else {
        screen_flip(screen);
        system_set_palette(&state->system,screen->palette);
    }

    system_blit(&state->system);
    system_flip(&state->system);
    
    system_delay(delay);
    // fade to black
}
