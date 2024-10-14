#include <math.h>

#include "screen.h"
#include "common.h"
#include "state.h"


void screen_init(screen_t *screen, system_t *system) {
    printf("Initializing screen...\n");
    screen->width = system->width;
    screen->height = system->height;
    screen->bpp = system->bpp;

    screen->back_buffer = (u8 *)memory_alloc(screen->width * screen->height * screen->bpp);
    screen->front_buffer = (u8 *)memory_alloc(screen->width * screen->height * screen->bpp);
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
