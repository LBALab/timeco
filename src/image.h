#pragma once

#include <math.h>

#include "common.h"
#include "file_system.h"

// see format: https://opensource.apple.com/source/tcl/tcl-20/tcl_ext/tkimg/tkimg/bmp/bmp.txt.auto.html
u8* image_read_rle(const u8 *filename) {
    FILE *file = file_open((char *)filename, "rb");

    if (!file) {
        printf("Error: could not open file %s\n", filename);
        return NULL;
    }
    
    file_seek(file, 0x12, 0);
    i32 width = file_read_i32(file);
    i32 height = file_read_i32(file);
    
    file_seek(file, 0x1C, 0);
    i32 bpp = file_read_i16(file);
    i16 compression = file_read_i16(file);

    i32 num_colours = pow(2, bpp);
    i32 size = width * height * bpp / 8;
    i32 pitch = width * (bpp >> 3);
    i32 pad = (((pitch) % 4) ? (4 - ((pitch) % 4)) : 0);

    printf("width: %d\n", width);
    printf("height: %d\n", height);
    printf("bpp: %d\n", bpp);
    printf("compression: %d\n", compression);
    printf("size: %d\n", size);
    printf("num_colours: %d\n", num_colours);
    printf("pad: %d\n", pad);

    file_seek(file, 0x36, 0);
    u8 palette[num_colours * 3];
    for (i32 i = 0; i < num_colours; i++) {
        palette[i * 3 + 0] = file_read_u8(file);
        palette[i * 3 + 1] = file_read_u8(file);
        palette[i * 3 + 2] = file_read_u8(file);
        file_read_u8(file);
    }

    u8 *pixels = (u8*)memory_alloc(size * 4);
    if (compression == 0) {
        for (i32 y = height - 1; y >= 0; y--) {
            for (i32 x = 0; x < width; x++) {
                u8 colour_index = file_read_u8(file);
                i32 index = y * width * 4 + x * 4;

                pixels[index + 0] = 0;
                pixels[index + 1] = palette[colour_index * 3 + 0];
                pixels[index + 2] = palette[colour_index * 3 + 1];
                pixels[index + 3] = palette[colour_index * 3 + 2];
            }
        }
    } else if (compression == 1) {
        i32 index = 0;
        i32 y = height - 1;
        while (index < size * 4) {
            u8 mode = file_read_u8(file);
            u8 value = file_read_u8(file);

            if (mode == 0) { // absolute mode
                if (value == 0) { // line end
                    y -= 1;
                    index = y * width * 4;
                    continue;
                } else if (value == 1) { // image end
                    break;
                } else if (value == 2) { // offset
                    u8 offset_x = file_read_u8(file);
                    u8 offset_y = file_read_u8(file);
                    y -= offset_y;
                    index += offset_y * width * 4 + offset_x * 4;
                } else { // encoded
                    u8 count = value;
                    for (i32 j = 0; j < count; j++) {
                        u8 colour_index = file_read_u8(file);
                        pixels[index + 0] = 0;
                        pixels[index + 1] = palette[colour_index * 3 + 0];
                        pixels[index + 2] = palette[colour_index * 3 + 1];
                        pixels[index + 3] = palette[colour_index * 3 + 2];
                        index += 4;
                    }
                    if((value & 1) == 1){
                        file_read_u8(file);
                    }
                }
            } else { // encoded
                u8 count = mode;
                u8 colour_index = value;
                for (i32 j = 0; j < count; j++) {
                    pixels[index + 0] = 0;
                    pixels[index + 1] = palette[colour_index * 3 + 0];
                    pixels[index + 2] = palette[colour_index * 3 + 1];
                    pixels[index + 3] = palette[colour_index * 3 + 2];
                    index += 4;
                }
            }
        }
    } else {
        printf("Error: compression type %d not supported\n", compression);
        return NULL;
    }

    file_close(file);
    return pixels;
}
