#include <math.h>

#include "pixel_colour.h"
#include "lib/common.h"


void pixel_colour_init(pixel_colour *pc, u32 value) {
    pc->val = value;
}

void pixel_colour_rgb(pixel_colour *pc, u8 R, u8 G, u8 B, u8 A) {
    pc->r = R;
    pc->g = G;
    pc->b = B;
    pc->a = A;
}

pixel_colour pixel_colour_diffuse(u8 *texture, vec2_t uv) {
    i32 width = 1024;
    i32 height = 1024;
    i32 bpp = 4;

    i32 x = (i32)(uv.x * width);
    i32 y = (i32)(uv.y * height);
    i32 index = (x + y * width) * bpp;

    pixel_colour colour;
    colour.r = texture[index + 0];
    colour.g = texture[index + 1];
    colour.b = texture[index + 2];
    colour.a = texture[index + 3];

    return colour;
}
