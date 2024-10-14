#pragma once

#include "renderer.h"
#include "common.h"
#include "system.h"
#include "pixel_colour.h"


typedef struct {
    i32 width;
    i32 height;
    i16 bpp;
    u8 *back_buffer;
    u8 *front_buffer;
    u8 *rendering_buffer;
    u8 *texture_buffer;
    u8 * stride_buffer;
    f32 *zbuffer;
    i32 triangles;
} renderer_t;


void renderer_init(renderer_t *renderer, system_t *system);
void renderer_release(renderer_t *renderer);

void renderer_flip_vertically(renderer_t *renderer);
void renderer_flip(renderer_t *renderer);
void renderer_clear(renderer_t *renderer);

void renderer_draw_line(u8 *pixels, i32 w, i32 h, i32 bpp, i32 x0, i32 y0, i32 x1, i32 y1, pixel_colour colour);
