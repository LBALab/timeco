#pragma once

#include "lib/common.h"
#include "system.h"
#include "geometry.h"


typedef struct pixel_colour_s {
    union {
        struct {
            u8 r, g, b, a;
        };
        u8 raw[4];
        u32 val;
    };
} pixel_colour;


void pixel_colour_init(pixel_colour *pc, u32 value);
void pixel_colour_rgb(pixel_colour *pc, u8 R, u8 G, u8 B, u8 A);
pixel_colour pixel_colour_diffuse(u8 *texture, vec2_t uv);
