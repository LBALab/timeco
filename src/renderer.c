#include <math.h>

#include "renderer.h"
#include "common.h"
#include "state.h"


void renderer_init(renderer_t *renderer, system_t *system) {
    printf("Initializing renderer...\n");
    i32 width = system->width;
    i32 height = system->height;
    i16 bpp = system->bpp;
    renderer->width = system->width;
    renderer->height = system->height;
    renderer->bpp = system->bpp;

    renderer->stride_buffer = (u8 *)memory_alloc(width * bpp);
    renderer->rendering_buffer = (u8 *)memory_alloc(width * height * bpp);
    renderer->zbuffer = (f32 *)memory_alloc(width * height * sizeof(f32));

    renderer->triangles = 0;
}

void renderer_release(renderer_t *renderer) {
    memory_free(renderer->rendering_buffer);
    memory_free(renderer->zbuffer);
    memory_free(renderer->stride_buffer);
}

void renderer_draw_line(u8 *pixels, i32 w, i32 h, i32 bpp, i32 x0, i32 y0, i32 x1, i32 y1, pixel_colour colour) {
    b8 steep = false;
    if (abs(x0 - x1) < abs(y0 - y1)) {
        swap(&x0, &y0);
        swap(&x1, &y1);
        steep = true;
    }
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    for (i32 x = x0; x <= x1; x++) {
        f32 t = (x - x0) / (f32)(x1 - x0);
        i32 y = y0 * (1.0f - t) + y1 * t;
        i32 index = (x + y * w) * bpp;
        if (steep) {
            index = (y + x * w) * bpp;
        }
        pixels[index + 0] = colour.a;
        pixels[index + 1] = colour.b;
        pixels[index + 2] = colour.g;
        pixels[index + 3] = colour.r;
    }
}

inline void renderer_flip_vertically(renderer_t *renderer) {
    const i32 width = renderer->width;
    const i32 height = renderer->height;
    const i32 bpp = renderer->bpp;
    const i32 stride = width * bpp;
    
    u8 *pixels = renderer->rendering_buffer;
    u8 *row = renderer->stride_buffer;
    memset(row, 0, stride);

    u8 *low = pixels;
    u8 *high = &pixels[(height - 1) * stride];

    for (; low < high; low += stride, high -= stride) {
        memcpy(row, low, stride);
        memcpy(low, high, stride);
        memcpy(high, row, stride);
    }
}

inline void renderer_flip(renderer_t *renderer, u8 *back_buffer) {
    i32 width = renderer->width;
    i32 height = renderer->height;
    i16 bpp = renderer->bpp;

    renderer_flip_vertically(renderer);
    memory_copy(back_buffer, renderer->rendering_buffer, width * height * bpp);
}

inline void renderer_clear(renderer_t *renderer) {
    i32 width = renderer->width;
    i32 height = renderer->height;
    i32 bpp = renderer->bpp;

    memset(renderer->zbuffer, -INT32_MAX, width * height * sizeof(i32));
    memset(renderer->rendering_buffer, 0, width * height * bpp * sizeof(u8));
}
