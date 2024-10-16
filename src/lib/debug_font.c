#include "common.h"


u32 font_size = 8;
u8 text_colour = 15;
u8 text_paper = -1;

u8 Font8x8[256*8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    126, 129, 165, 129, 189, 153, 129, 126,
    126, 255, 219, 255, 195, 231, 255, 126,
    108, 254, 254, 254, 124, 56, 16, 0,
    16, 56, 124, 254, 124, 56, 16, 0,
    56, 124, 56, 254, 254, 146, 16, 124,
    0, 16, 56, 124, 254, 124, 56, 124,
    0, 0, 24, 60, 60, 24, 0, 0,
    255, 255, 231, 195, 195, 231, 255, 255,
    0, 60, 102, 66, 66, 102, 60, 0,
    255, 195, 153, 189, 189, 153, 195, 255,
    15, 7, 15, 125, 204, 204, 204, 120,
    60, 102, 102, 102, 60, 24, 126, 24,
    63, 51, 63, 48, 48, 112, 240, 224,
    127, 99, 127, 99, 99, 103, 230, 192,
    153, 90, 60, 231, 231, 60, 90, 153,
    128, 224, 248, 254, 248, 224, 128, 0,
    2, 14, 62, 254, 62, 14, 2, 0,
    24, 60, 126, 24, 24, 126, 60, 24,
    102, 102, 102, 102, 102, 0, 102, 0,
    127, 219, 219, 123, 27, 27, 27, 0,
    62, 99, 56, 108, 108, 56, 134, 252,
    0, 0, 0, 0, 126, 126, 126, 0,
    24, 60, 126, 24, 126, 60, 24, 255,
    24, 60, 126, 24, 24, 24, 24, 0,
    24, 24, 24, 24, 126, 60, 24, 0,
    0, 24, 12, 254, 12, 24, 0, 0,
    0, 48, 96, 254, 96, 48, 0, 0,
    0, 0, 192, 192, 192, 254, 0, 0,
    0, 36, 102, 255, 102, 36, 0, 0,
    0, 24, 60, 126, 255, 255, 0, 0,
    0, 255, 255, 126, 60, 24, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    24, 60, 60, 24, 24, 0, 24, 0,
    108, 108, 108, 0, 0, 0, 0, 0,
    108, 108, 254, 108, 254, 108, 108, 0,
    24, 126, 192, 124, 6, 252, 24, 0,
    0, 198, 204, 24, 48, 102, 198, 0,
    56, 108, 56, 118, 220, 204, 118, 0,
    48, 48, 96, 0, 0, 0, 0, 0,
    24, 48, 96, 96, 96, 48, 24, 0,
    96, 48, 24, 24, 24, 48, 96, 0,
    0, 102, 60, 255, 60, 102, 0, 0,
    0, 24, 24, 126, 24, 24, 0, 0,
    0, 0, 0, 0, 0, 24, 24, 48,
    0, 0, 0, 126, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 24, 24, 0,
    6, 12, 24, 48, 96, 192, 128, 0,
    124, 206, 222, 246, 230, 198, 124, 0,
    48, 112, 48, 48, 48, 48, 252, 0,
    120, 204, 12, 56, 96, 204, 252, 0,
    120, 204, 12, 56, 12, 204, 120, 0,
    28, 60, 108, 204, 254, 12, 30, 0,
    252, 192, 248, 12, 12, 204, 120, 0,
    56, 96, 192, 248, 204, 204, 120, 0,
    252, 204, 12, 24, 48, 48, 48, 0,
    120, 204, 204, 120, 204, 204, 120, 0,
    120, 204, 204, 124, 12, 24, 112, 0,
    0, 24, 24, 0, 0, 24, 24, 0,
    0, 24, 24, 0, 0, 24, 24, 48,
    24, 48, 96, 192, 96, 48, 24, 0,
    0, 0, 126, 0, 126, 0, 0, 0,
    96, 48, 24, 12, 24, 48, 96, 0,
    60, 102, 12, 24, 24, 0, 24, 0,
    124, 198, 222, 222, 220, 192, 124, 0,
    48, 120, 204, 204, 252, 204, 204, 0,
    252, 102, 102, 124, 102, 102, 252, 0,
    60, 102, 192, 192, 192, 102, 60, 0,
    248, 108, 102, 102, 102, 108, 248, 0,
    254, 98, 104, 120, 104, 98, 254, 0,
    254, 98, 104, 120, 104, 96, 240, 0,
    60, 102, 192, 192, 206, 102, 58, 0,
    204, 204, 204, 252, 204, 204, 204, 0,
    120, 48, 48, 48, 48, 48, 120, 0,
    30, 12, 12, 12, 204, 204, 120, 0,
    230, 102, 108, 120, 108, 102, 230, 0,
    240, 96, 96, 96, 98, 102, 254, 0,
    198, 238, 254, 254, 214, 198, 198, 0,
    198, 230, 246, 222, 206, 198, 198, 0,
    56, 108, 198, 198, 198, 108, 56, 0,
    252, 102, 102, 124, 96, 96, 240, 0,
    124, 198, 198, 198, 214, 124, 14, 0,
    252, 102, 102, 124, 108, 102, 230, 0,
    124, 198, 224, 120, 14, 198, 124, 0,
    252, 180, 48, 48, 48, 48, 120, 0,
    204, 204, 204, 204, 204, 204, 252, 0,
    204, 204, 204, 204, 204, 120, 48, 0,
    198, 198, 198, 198, 214, 254, 108, 0,
    198, 198, 108, 56, 108, 198, 198, 0,
    204, 204, 204, 120, 48, 48, 120, 0,
    254, 198, 140, 24, 50, 102, 254, 0,
    120, 96, 96, 96, 96, 96, 120, 0,
    192, 96, 48, 24, 12, 6, 2, 0,
    120, 24, 24, 24, 24, 24, 120, 0,
    16, 56, 108, 198, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 255,
    48, 48, 24, 0, 0, 0, 0, 0,
    0, 0, 120, 12, 124, 204, 118, 0,
    224, 96, 96, 124, 102, 102, 220, 0,
    0, 0, 120, 204, 192, 204, 120, 0,
    28, 12, 12, 124, 204, 204, 118, 0,
    0, 0, 120, 204, 252, 192, 120, 0,
    56, 108, 100, 240, 96, 96, 240, 0,
    0, 0, 118, 204, 204, 124, 12, 248,
    224, 96, 108, 118, 102, 102, 230, 0,
    48, 0, 112, 48, 48, 48, 120, 0,
    12, 0, 28, 12, 12, 204, 204, 120,
    224, 96, 102, 108, 120, 108, 230, 0,
    112, 48, 48, 48, 48, 48, 120, 0,
    0, 0, 204, 254, 254, 214, 214, 0,
    0, 0, 184, 204, 204, 204, 204, 0,
    0, 0, 120, 204, 204, 204, 120, 0,
    0, 0, 220, 102, 102, 124, 96, 240,
    0, 0, 118, 204, 204, 124, 12, 30,
    0, 0, 220, 118, 98, 96, 240, 0,
    0, 0, 124, 192, 112, 28, 248, 0,
    16, 48, 252, 48, 48, 52, 24, 0,
    0, 0, 204, 204, 204, 204, 118, 0,
    0, 0, 204, 204, 204, 120, 48, 0,
    0, 0, 198, 198, 214, 254, 108, 0,
    0, 0, 198, 108, 56, 108, 198, 0,
    0, 0, 204, 204, 204, 124, 12, 248,
    0, 0, 252, 152, 48, 100, 252, 0,
    28, 48, 48, 224, 48, 48, 28, 0,
    24, 24, 24, 0, 24, 24, 24, 0,
    224, 48, 48, 28, 48, 48, 224, 0,
    118, 220, 0, 0, 0, 0, 0, 0,
    0, 16, 56, 108, 198, 198, 254, 0,
    124, 198, 192, 198, 124, 12, 6, 124,
    0, 204, 0, 204, 204, 204, 118, 0,
    28, 0, 120, 204, 252, 192, 120, 0,
    126, 129, 60, 6, 62, 102, 59, 0,
    204, 0, 120, 12, 124, 204, 118, 0,
    224, 0, 120, 12, 124, 204, 118, 0,
    48, 48, 120, 12, 124, 204, 118, 0,
    0, 0, 124, 198, 192, 120, 12, 56,
    126, 129, 60, 102, 126, 96, 60, 0,
    204, 0, 120, 204, 252, 192, 120, 0,
    224, 0, 120, 204, 252, 192, 120, 0,
    204, 0, 112, 48, 48, 48, 120, 0,
    124, 130, 56, 24, 24, 24, 60, 0,
    224, 0, 112, 48, 48, 48, 120, 0,
    198, 16, 124, 198, 254, 198, 198, 0,
    48, 48, 0, 120, 204, 252, 204, 0,
    28, 0, 252, 96, 120, 96, 252, 0,
    0, 0, 127, 12, 127, 204, 127, 0,
    62, 108, 204, 254, 204, 204, 206, 0,
    120, 132, 0, 120, 204, 204, 120, 0,
    0, 204, 0, 120, 204, 204, 120, 0,
    0, 224, 0, 120, 204, 204, 120, 0,
    120, 132, 0, 204, 204, 204, 118, 0,
    0, 224, 0, 204, 204, 204, 118, 0,
    0, 204, 0, 204, 204, 124, 12, 248,
    195, 24, 60, 102, 102, 60, 24, 0,
    204, 0, 204, 204, 204, 204, 120, 0,
    24, 24, 126, 192, 192, 126, 24, 24,
    56, 108, 100, 240, 96, 230, 252, 0,
    204, 204, 120, 48, 252, 48, 252, 48,
    248, 204, 204, 250, 198, 207, 198, 195,
    14, 27, 24, 60, 24, 24, 216, 112,
    28, 0, 120, 12, 124, 204, 118, 0,
    56, 0, 112, 48, 48, 48, 120, 0,
    0, 28, 0, 120, 204, 204, 120, 0,
    0, 28, 0, 204, 204, 204, 118, 0,
    0, 248, 0, 184, 204, 204, 204, 0,
    252, 0, 204, 236, 252, 220, 204, 0,
    60, 108, 108, 62, 0, 126, 0, 0,
    56, 108, 108, 56, 0, 124, 0, 0,
    24, 0, 24, 24, 48, 102, 60, 0,
    0, 0, 0, 252, 192, 192, 0, 0,
    0, 0, 0, 252, 12, 12, 0, 0,
    198, 204, 216, 54, 107, 194, 132, 15,
    195, 198, 204, 219, 55, 109, 207, 3,
    24, 0, 24, 24, 60, 60, 24, 0,
    0, 51, 102, 204, 102, 51, 0, 0,
    0, 204, 102, 51, 102, 204, 0, 0,
    34, 136, 34, 136, 34, 136, 34, 136,
    85, 170, 85, 170, 85, 170, 85, 170,
    219, 246, 219, 111, 219, 126, 215, 237,
    24, 24, 24, 24, 24, 24, 24, 24,
    24, 24, 24, 24, 248, 24, 24, 24,
    24, 24, 248, 24, 248, 24, 24, 24,
    54, 54, 54, 54, 246, 54, 54, 54,
    0, 0, 0, 0, 254, 54, 54, 54,
    0, 0, 248, 24, 248, 24, 24, 24,
    54, 54, 246, 6, 246, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54,
    0, 0, 254, 6, 246, 54, 54, 54,
    54, 54, 246, 6, 254, 0, 0, 0,
    54, 54, 54, 54, 254, 0, 0, 0,
    24, 24, 248, 24, 248, 0, 0, 0,
    0, 0, 0, 0, 248, 24, 24, 24,
    24, 24, 24, 24, 31, 0, 0, 0,
    24, 24, 24, 24, 255, 0, 0, 0,
    0, 0, 0, 0, 255, 24, 24, 24,
    24, 24, 24, 24, 31, 24, 24, 24,
    0, 0, 0, 0, 255, 0, 0, 0,
    24, 24, 24, 24, 255, 24, 24, 24,
    24, 24, 31, 24, 31, 24, 24, 24,
    54, 54, 54, 54, 55, 54, 54, 54,
    54, 54, 55, 48, 63, 0, 0, 0,
    0, 0, 63, 48, 55, 54, 54, 54,
    54, 54, 247, 0, 255, 0, 0, 0,
    0, 0, 255, 0, 247, 54, 54, 54,
    54, 54, 55, 48, 55, 54, 54, 54,
    0, 0, 255, 0, 255, 0, 0, 0,
    54, 54, 247, 0, 247, 54, 54, 54,
    24, 24, 255, 0, 255, 0, 0, 0,
    54, 54, 54, 54, 255, 0, 0, 0,
    0, 0, 255, 0, 255, 24, 24, 24,
    0, 0, 0, 0, 255, 54, 54, 54,
    54, 54, 54, 54, 63, 0, 0, 0,
    24, 24, 31, 24, 31, 0, 0, 0,
    0, 0, 31, 24, 31, 24, 24, 24,
    0, 0, 0, 0, 63, 54, 54, 54,
    54, 54, 54, 54, 255, 54, 54, 54,
    24, 24, 255, 24, 255, 24, 24, 24,
    24, 24, 24, 24, 248, 0, 0, 0,
    0, 0, 0, 0, 31, 24, 24, 24,
    255, 255, 255, 255, 255, 255, 255, 255,
    0, 0, 0, 0, 255, 255, 255, 255,
    240, 240, 240, 240, 240, 240, 240, 240,
    15, 15, 15, 15, 15, 15, 15, 15,
    255, 255, 255, 255, 0, 0, 0, 0,
    0, 0, 118, 220, 200, 220, 118, 0,
    0, 120, 204, 248, 204, 248, 192, 192,
    0, 252, 204, 192, 192, 192, 192, 0,
    0, 0, 254, 108, 108, 108, 108, 0,
    252, 204, 96, 48, 96, 204, 252, 0,
    0, 0, 126, 216, 216, 216, 112, 0,
    0, 102, 102, 102, 102, 124, 96, 192,
    0, 118, 220, 24, 24, 24, 24, 0,
    252, 48, 120, 204, 204, 120, 48, 252,
    56, 108, 198, 254, 198, 108, 56, 0,
    56, 108, 198, 198, 108, 108, 238, 0,
    28, 48, 24, 124, 204, 204, 120, 0,
    0, 0, 126, 219, 219, 126, 0, 0,
    6, 12, 126, 219, 219, 126, 96, 192,
    56, 96, 192, 248, 192, 96, 56, 0,
    120, 204, 204, 204, 204, 204, 204, 0,
    0, 126, 0, 126, 0, 126, 0, 0,
    24, 24, 126, 24, 24, 0, 126, 0,
    96, 48, 24, 48, 96, 0, 252, 0,
    24, 48, 96, 48, 24, 0, 252, 0,
    14, 27, 27, 24, 24, 24, 24, 24,
    24, 24, 24, 24, 24, 216, 216, 112,
    24, 24, 0, 126, 0, 24, 24, 0,
    0, 118, 220, 0, 118, 220, 0, 0,
    56, 108, 108, 56, 0, 0, 0, 0,
    0, 0, 0, 24, 24, 0, 0, 0,
    0, 0, 0, 0, 24, 0, 0, 0,
    15, 12, 12, 12, 236, 108, 60, 28,
    88, 108, 108, 108, 108, 0, 0, 0,
    112, 152, 48, 96, 248, 0, 0, 0,
    0, 0, 60, 60, 60, 60, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void debug_set_colour(u8 colour)
{
    text_colour = colour;
}

void debug_draw_text(u8* screen_buffer, i32 x, i32 y, char *str)
{
    u8 character;
    u8 line;
    i32 mask;
    u8 *ptr;
    u8 *font;
    u8 *buffer = (u8 *)screen_buffer + (640 * y) + x;

    if (!str) {
        return;
    }

    while((character = *str++) != 0)
    {
        ptr = buffer;
        font = &Font8x8[character * font_size];

        for(u32 pos = font_size; pos > 0; --pos)
        {
            line = *font++;
            mask = 0x80;
            while(mask > 0)
            {
                if (line & mask) {
                    *ptr = text_colour;
                }
                ptr++;
                mask >>= 1;
            }

            ptr += 640 - font_size;
        }

        buffer += font_size;
    }
}
