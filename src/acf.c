#include <string.h>
#include <stdio.h>

#include "lib/common.h"
#include "lib/file_reader.h"
#include "lib/debug_font.h"

#include "acf.h"

// based on:
// https://blog.defence-force.org/index.php?page=articles&ref=ART82
// https://blog.defence-force.org/files/time_commando/ACF2PCX.cpp
// https://github.com/LBALab/lba2-classic-community/blob/main/SOURCES/DEC.ASM
// https://github.com/LBALab/lba2-classic-community/blob/main/SOURCES/DEC.H
// https://github.com/LBALab/lba2-classic-community/blob/main/SOURCES/DEC_XCF.ASM
// https://github.com/LBALab/lba2-classic-community/blob/main/SOURCES/DEC_XCF.H


enum chunk_type_e {
    CHUNK_TYPE_UNKNOWN = 0,
    CHUNK_TYPE_END = 1,
    CHUNK_TYPE_FRAMELEN = 2,
    CHUNK_TYPE_FORMAT = 3,
    CHUNK_TYPE_PALETTE = 4,
    CHUNK_TYPE_NULCHUNK = 5,
    CHUNK_TYPE_KEYFRAME = 6,
    CHUNK_TYPE_DLTFRAME = 7,
    CHUNK_TYPE_COVERS = 8,
    CHUNK_TYPE_CAMERA = 9,
    CHUNK_TYPE_SOUNDBUF = 10,
    CHUNK_TYPE_SOUNDFRM = 11,
    CHUNK_TYPE_SOUNDEND = 12,
    CHUNK_TYPE_SAL_STRT = 13,
    CHUNK_TYPE_SAL_PART = 14,
    CHUNK_TYPE_SAL_END = 15,
    CHUNK_TYPE_SAL_COMP = 16,
};

#pragma pack(1)
typedef struct {
    u32 biggest_frame_size;
    u8 frame_size_in_sectors;
} frame_len_t;

#pragma pack(1)
typedef struct {
    u32 colour_offset;
    u8 opcodes[30];
} frame_data_t;

#pragma pack(1)
typedef struct {
    u32 struct_size;
    u32 width;
    u32 height;
    u32 frame_size;
    u32 key_size;
    u32 key_rate;
    u32 play_rate;
    u32 sampling_rate;
    u32 sample_type;
    u32 sample_flags;
    u32 compressor; // 0 - ACF, 1 - XCF
} format_t;

#pragma pack(1)
typedef struct {
    i32 x;
    i32 y;
    i32 z;
    i32 target_x;
    i32 target_y;
    i32 target_z;
    i32 roll;
    i32 fov;
} camera_t;

#pragma pack(1)
typedef struct {
    u8 name[8];
    u32 size;
} chunk_t;


u32 diagonal_offsets_1[64] = {
    0, 1, 320, 640, 321, 2, 3, 322, 641, 960, 1280, 961, 642, 323, 4, 5, 324, 643, 962, 1281, 1600, 1920, 1601, 1282, 963, 644, 325, 6, 7,
    326, 645,  964, 1283, 1602, 1921, 2240, 2241, 1922, 1603, 1284, 965, 646, 327, 647, 966, 1285, 1604, 1923, 2242, 2243, 1924, 1605, 1286,
    967, 1287, 1606, 1925, 2244, 2245, 1926, 1607, 1927, 2246, 2247
};

u32 diagonal_offsets_2[64] = {
    7, 6, 327, 647, 326, 5, 4, 325, 646, 967, 1287, 966, 645, 324, 3, 2, 323, 644, 965, 1286, 1607, 1927, 1606, 1285, 964, 643, 322, 1, 0,
    321, 642, 963, 1284, 1605, 1926, 2247, 2246, 1925, 1604, 1283, 962, 641, 320, 640, 961, 1282, 1603, 1924, 2245, 2244, 1923, 1602, 1281,
    960, 1280, 1601, 1922, 2243, 2242, 1921, 1600, 1920, 2241, 2240
};

u32 split_tile_offsets[4] = { 0, 4, 320*4, 320*4 + 4 };


i32 frame_width = 320;
i32 frame_height = 240;

i32 frame_number = 0;
char frame_text[12];

chunk_t* current_chunk = NULL;
format_t* format = NULL;
frame_len_t* frame_len = NULL;
camera_t* camera = NULL;
u8 palette[256 * 3];

u8* previous_buffer;
u8* previous_frame_buffer;
u8* previous_tile;
u8* current_buffer;
u8* current_tile;

u8* aligned_stream = NULL;
u8* unaligned_stream = NULL;



inline void set_pixel(i32 x, i32 y, u8 colour) {
    current_tile[x + (y * frame_width)] = colour;
}

// 3 bytes (6 bits x 4) for the position, 4 bytes for colors
void update_4() {
    u32 value = *(u32*)unaligned_stream;
    unaligned_stream += 3;

    for (i32 i = 0; i < 4; i++) {
        set_pixel(value & 7 , ((value >> 3) & 7), *aligned_stream++);
        value >>= 6;
    }
}

void update_8() {
    update_4();
    update_4();
}

void update_16()
 {
    for (i32 y = 0; y < 8; y++) {
        u8 mask = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (mask & 1) {
                set_pixel(x, y, *unaligned_stream++);
            }
            mask >>= 1;
        }
    }
}

void block_copy_8x8(u8* dest, u8* source) {
    for (i32 y = 0; y < 8; y++) {
      memcpy(dest + y * frame_width, source + y * frame_width, 8);
    }
}

void block_copy_4x4(u8* dest, u8* source) {
    for (i32 y = 0; y < 4; y++) {
      memcpy(dest + y * frame_width, source + y * frame_width, 4);
    }
}

void zero_motion_decode() {
    block_copy_8x8(current_tile, previous_tile);
}

void short_motion_8_decode() {
    i32 value = *unaligned_stream++;
    i32 dx = (((value & 15) << 28) >> 28);
    i32 dy = ((value << 24) >> 28);
    block_copy_8x8(current_tile, previous_tile + (4 + frame_width * 4) + dx + dy * frame_width);
}

void short_motion_4_decode() {
    i32 value = *aligned_stream++;
    i32 dx = (((value & 15) << 28) >> 28);
    i32 dy = ((value << 24) >> 28);
    block_copy_4x4(current_tile, previous_tile + 2 + frame_width * 2 + dx + dy * frame_width);

    value = *aligned_stream++;
    dx = (((value & 15) << 28) >> 28);
    dy = ((value << 24) >> 28);
    block_copy_4x4(current_tile + 4, previous_tile + 2 + frame_width * 2 + dx + dy * frame_width + 4);

    value = *aligned_stream++;
    dx = (((value & 15) << 28) >> 28);
    dy = ((value << 24) >> 28);
    block_copy_4x4(current_tile + frame_width * 4, previous_tile + 2 + frame_width * 2 + dx + dy * frame_width + frame_width * 4);

    value = *aligned_stream++;
    dx = (((value & 15) << 28) >> 28);
    dy = ((value << 24) >> 28);
    block_copy_4x4(current_tile + frame_width * 4 + 4, previous_tile + 2 + frame_width * 2 + dx + dy * frame_width + frame_width * 4 + 4);
}

void motion_8_decode() {
    block_copy_8x8(current_tile, previous_frame_buffer + (*(u16*)unaligned_stream));
    unaligned_stream += 2;
}

void motion_4_decode() {
    block_copy_4x4(current_tile, previous_frame_buffer + read_u16(aligned_stream));
    block_copy_4x4(current_tile + 4, previous_frame_buffer + read_u16(aligned_stream));
    block_copy_4x4(current_tile + frame_width * 4, previous_frame_buffer + read_u16(aligned_stream));
    block_copy_4x4(current_tile + frame_width * 4 + 4, previous_frame_buffer + read_u16(aligned_stream));
}

void ro_motion_8_decode() {
    block_copy_8x8(current_tile, previous_tile + read_s16(unaligned_stream) + 4 + frame_width * 4);
}

void ro_motion_4_decode() {
    block_copy_4x4(current_tile, previous_tile + read_s16(aligned_stream) + 2 + frame_width * 2);
    block_copy_4x4(current_tile + 4, previous_tile + 4 + read_s16(aligned_stream) + 2 + frame_width * 2);
    block_copy_4x4(current_tile + frame_width * 4, previous_tile + frame_width * 4 + read_s16(aligned_stream) + 2 + frame_width * 2);
    block_copy_4x4(current_tile + frame_width * 4 + 4, previous_tile + frame_width * 4 + 4 + read_s16(aligned_stream) + 2 + frame_width * 2);
}

void rc_motion_8_decode() {
    block_copy_8x8(current_tile, previous_tile + read_xy_offset(unaligned_stream,frame_width) + 4 + frame_width * 4);
}

void rc_motion_4_decode() {
    block_copy_4x4(current_tile, previous_tile + read_xy_offset(aligned_stream, frame_width) + 2 + frame_width * 2);
    block_copy_4x4(current_tile + 4, previous_tile + read_xy_offset(aligned_stream, frame_width) + 2 + frame_width * 2 + 4);
    block_copy_4x4(current_tile + frame_width * 4, previous_tile + read_xy_offset(aligned_stream, frame_width) + 2 + frame_width * 2 + frame_width * 4);
    block_copy_4x4(current_tile + frame_width * 4 + 4, previous_tile + read_xy_offset(aligned_stream, frame_width) + 2 + frame_width * 2 + frame_width * 4 + 4);
}

// load one byte, apply it to the entire tile
void single_colour_fill_decode() {
    u8 colour_tile = *unaligned_stream++;
    for (i32 y = 0; y < 8; y++) {
        memset(current_tile + y * frame_width, colour_tile, 8);
    }
}

// Load four bytes, one for each quadrant of the tile
void four_color_fill_decode() {
    u8 colour_top_left = *aligned_stream++;
    u8 colour_top_right = *aligned_stream++;
    u8 colour_bottom_left = *aligned_stream++;
    u8 colour_bottom_right = *aligned_stream++;

    for (i32 y = 0; y < 4; y++) {
      memset(current_tile + y * frame_width, colour_top_left, 4);
      memset(current_tile + y * frame_width + 4, colour_top_right, 4);
      memset(current_tile + (y + 4) * frame_width, colour_bottom_left, 4);
      memset(current_tile + (y + 4) * frame_width + 4, colour_bottom_right, 4);
    }
}

// 10 octets:
// - 8 octets format 8x8x1 bits for each colour
// - 2 octets colour (palette index)
void one_bit_tile_decode() {
    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            set_pixel(x, y, unaligned_stream[a & 1]);
            a >>= 1;
        }
    }
    unaligned_stream += 2;
}

// 20 octets:
// - 4 octets colour (palette index)
// - 16 octets format 8x8x2 bits for each colour
void two_bit_tile_decode() {
    const u8* colors = aligned_stream;
    aligned_stream += 4;
    for (i32 y = 0; y < 8; y++) {
        i32 a = *(u16*)aligned_stream;
        aligned_stream += 2;
        for (i32 x = 0; x < 8; x++) {
            set_pixel(x, y, colors[a & 3]);
            a >>= 2;
        }
    }
}

// 32 octets:
// - 24 octets format 8x8x3 bits for each colour
// - 8 octets colour (palette index)
void three_bit_tile_decode() {
    for (i32 y = 0; y < 8; y++) {
        u32 a = read_u32(aligned_stream, 3);
        for (i32 x = 0; x < 8; x++) {
            set_pixel(x, y, unaligned_stream[a & 7]);
            a >>= 3;
        }
    }
    unaligned_stream += 8;
}

// 48 octets:
// - 32 octets format 8x8x4 bits for each colour
// - 16 octets colour (palette index)
void four_bit_tile_decode() {
    for (i32 y = 0; y < 8; y++) {
        u32 a = read_u32(aligned_stream, 4);
        for (i32 x = 0; x < 8; x++) {
            set_pixel(x, y, unaligned_stream[a & 15]);
            a >>= 4;
        }
    }
    unaligned_stream += 16;
}

void one_bit_split_tile_decode() {
    for (u32 i = 0; i < 4; i++) {
        u32 offset = split_tile_offsets[i];
        u16 a = read_u16(aligned_stream);
        for (i32 y = 0; y < 4; y++) {
            for (i32 x = 0; x < 4; x++) {
                current_tile[x + y * frame_width + offset] = aligned_stream[a & 1];
                a >>= 1;
            }
        }
        aligned_stream += 2;
    }
} 

void two_bit_split_tile_decode() {
    for (u32 i = 0; i < 4; i++) {
        u32 offset = split_tile_offsets[i];
        u32 a = read_u32(aligned_stream, 4);
        for (i32 y = 0; y < 4; y++) {
            for (i32 x = 0; x < 4; x++) {
                current_tile[x + y * frame_width + offset] = aligned_stream[a & 3];
                a >>= 2;
            }
        }
        aligned_stream += 4;
    }
}

void three_bit_split_tile_decode() {
    for (u32 i = 0; i < 4; i++) {
        u32 offset = split_tile_offsets[i];
        u32 a;
        for (i32 y = 0; y < 4; y++) {
            if (!(y & 1)) {
                a = read_u32(aligned_stream, 3);
            }
            for (i32 x = 0; x < 4; x++) {
                current_tile[x + y * frame_width + offset] = unaligned_stream[a & 7];
                a >>= 3;
            }
        }
        unaligned_stream += 8;
    }
}

// 20 bytes:
// - 4 octets (Couleurs de base)
// - 16 octets (4x4) pour indiquer les correspondances.
void cross_decode() {
    u32 value = read_u32(aligned_stream, 4);
    for (u32 i = 0; i < 4; i++) {
        u32 offset = split_tile_offsets[i];
        u8* dest = current_tile + offset;
        if (value & 1) {
            dest[0] = aligned_stream[1];
        } else {
            dest[0] = aligned_stream[0];
        }

        dest[0] = aligned_stream[(value & 1)];
        dest[1] = aligned_stream[0];
        dest[2] = aligned_stream[0];
        dest[3] = aligned_stream[((value & 2) >> 1) * 3];

        dest[320] = aligned_stream[1];
        dest[321] = aligned_stream[(value & 4) >> 2];
        dest[322] = aligned_stream[((value & 8) >> 3) * 3];
        dest[323] = aligned_stream[3];

        dest[640] = aligned_stream[1];
        dest[641] = aligned_stream[1 + ((value & 16) >> 4)];
        dest[642] = aligned_stream[2 + ((value & 32) >> 5)];
        dest[643] = aligned_stream[3];

        dest[960] = aligned_stream[1 + ((value & 64) >> 6)];
        dest[961] = aligned_stream[2];
        dest[962] = aligned_stream[2];
        dest[963] = aligned_stream[2 + ((value & 128) >> 7)];

        aligned_stream += 4;
        value >>= 8;
    }
}

void prime_decode() {
    i32 prime_colour = *unaligned_stream++;
    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                set_pixel(x, y, *unaligned_stream++);
            } else {
                set_pixel(x, y, prime_colour);
            }
            a >>= 1;
        }
    }
}

// All 64 colors to directly copy to the buffer
void raw_tile_decode() {
    for (i32 y = 0; y < 8; y++) {
        memcpy(current_tile + y * frame_width, aligned_stream, 8);
        aligned_stream += 8;
    }
}

// Similar to RawTileDecode, but all the colors are in the same bank, thus using only 4 bits per pixel
void one_bank_tile_decode() {
    u8 bank = *unaligned_stream++;
    for (i32 y = 0; y < 8; y++) {
        for (i32 x = 0; x < 8; x++) {
            if (x & 1) {
                set_pixel(x, y, bank + ((*aligned_stream++) >> 4));
            } else {
                set_pixel(x, y, bank + ((*aligned_stream) & 15));
            }
        }
    }
}

// Similar to OneBankTileDecode, but with colors in two different banks, and thus using 5 bits per pixel
// 41 octets:
// - 40 octets formant 8x8x5 bits which define the colour (in the range [0,15]), and the bank number.
// - 1 octet formant 2x4 bits which give the numbers of the 2 color banks to use. (You have to multiply by 16)
void two_banks_tile_decode() {
    u8 bank[2];

    bank[0] = ((*unaligned_stream) & 0x0f) << 4;
    bank[1] = ((*unaligned_stream) & 0xf0);
    unaligned_stream++;

    for (u32 y = 0; y < 8; y++) {
        u32 part1 = *(i32*)aligned_stream;
        u32 part2 = *(i32*)(aligned_stream + 4);
        aligned_stream += 5;
        for (u32 x = 0; x < 8; x++) {
            set_pixel(x, y, bank[(part1 & 16) >> 4] + (part1 & 15));
            part1 >>= 5;
            part1 |= (part2 << 27);
            part2 >>= 5;
        }
    }
}

void block_decode_horizontal() {
    u8 last_colour = 0;

    for (u32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (u32 x = 0; x < 8; x++) {
            if (a & 1) {
                last_colour = *unaligned_stream++;
            }
            a >>= 1;
            set_pixel(x, y, last_colour);
        }
    }
}

void block_decode_vertical() {
    u8 last_colour = 0;

    for (i32 x = 0; x < 8; x++) {
        u8 a = *aligned_stream++;
        for (i32 y = 0; y < 8; y++) {
            if (a & 1) {
                last_colour = *unaligned_stream++;
            }
            a >>= 1;
            set_pixel(x, y, last_colour);
        }
    }
}

void block_decode_2() {
    u8 last_colour = 0;
    u32* offsets = diagonal_offsets_1;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                last_colour = *unaligned_stream++;
            }
            a >>= 1;
            current_tile[*offsets++] = last_colour;
        }
    }
}

void block_decode_3() {
    u8 last_colour = 0;
    u32* offsets = diagonal_offsets_2;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                last_colour = *unaligned_stream++;
            }
            a >>= 1;
            current_tile[*offsets++] = last_colour;
        }
    }
}

void block_bank_1_decode_horizontal() {
    u8 last_colour = 0;
    u8 bank = (*unaligned_stream) << 4;
    u8 flag = 1;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                if (flag) {
                    last_colour = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_colour = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            set_pixel(x, y, bank + last_colour);
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void block_bank_1_decode_vertical() {
    u8 last_colour = 0;
    u8 bank = (*unaligned_stream) << 4;
    u8 flag = 1;

    for (i32 x = 0; x < 8; x++) {
        u8 a = *aligned_stream++;
        for (i32 y = 0; y < 8; y++) {
            if (a & 1) {
                if (flag) {
                    last_colour = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_colour = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            set_pixel(x, y, bank + last_colour);
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void block_bank_1_decode_2() {
    u8 last_colour = 0;
    u8 bank = (*unaligned_stream) << 4;
    u8 flag = 1;
    u32* offsets = diagonal_offsets_1;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                if (flag) {
                    last_colour = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_colour = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            current_tile[*offsets++] = bank + last_colour;
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void block_bank_1_decode_3() {
    u8 last_colour = 0;
    u8 bank = (*unaligned_stream) << 4;
    u8 flag = 1;
    u32* offsets = diagonal_offsets_2;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                if (flag) {
                    last_colour = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_colour = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            current_tile[*offsets++] = bank + last_colour;
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void scale_2x(state_t *state) {
    u8* source = (u8*)current_buffer;
    u8* dest = (u8*)state->screen.back_buffer;

    // scale 2x current buffer of 320x240 to 640x480
    for (int y = 0; y < 240; ++y) {
        for (int x = 0; x < 320; ++x) {
            u8 pixel = source[y * 320 + x];
            int dest_index = (y * 2 * 640) + (x * 2);

            dest[dest_index] = pixel;
            dest[dest_index + 1] = pixel;
            memcpy(dest + dest_index + 640, dest + dest_index, 2);
        }
    }
}

void decompress_frame(state_t *state, frame_data_t *frame_data) {
    previous_tile = previous_frame_buffer = previous_buffer;
    current_tile = current_buffer;

    unaligned_stream = (u8*)frame_data + frame_data->colour_offset;
    aligned_stream = (u8*)frame_data->opcodes + (frame_height / 8) * 30;

    i32 opcode = -1;
    const u8* opcode_ptr = frame_data->opcodes;

    for (i32 y = 0; y < frame_height / 8; y++) {
        for (i32 x = 0; x < frame_width / 8; x++) {
            if (opcode == -1) {
                opcode = ((*(i32*)opcode_ptr) | 0xff000000);
                opcode_ptr += 3;
            }

            switch (opcode & 63) {
                case 0: raw_tile_decode(); break;

                case 1: zero_motion_decode(); break;
                case 2: zero_motion_decode(); update_4(); break;
                case 3: zero_motion_decode(); update_8(); break;
                case 4: zero_motion_decode(); update_16(); break;

                case 5: short_motion_8_decode(); break;
                case 6: short_motion_8_decode(); update_4(); break;
                case 7: short_motion_8_decode(); update_8(); break;
                case 8: short_motion_8_decode(); update_16(); break;

                case 9:  motion_8_decode(); break;
                case 10: motion_8_decode(); update_4(); break;
                case 11: motion_8_decode(); update_8(); break;
                case 12: motion_8_decode(); update_16(); break;

                case 13: short_motion_4_decode(); break;
                case 14: short_motion_4_decode(); update_4(); break;
                case 15: short_motion_4_decode(); update_8(); break;
                case 16: short_motion_4_decode(); update_16(); break;

                case 17: motion_4_decode(); break;
                case 18: motion_4_decode(); update_4(); break;
                case 19: motion_4_decode(); update_8(); break;
                case 20: motion_4_decode(); update_16(); break;

                case 21: single_colour_fill_decode(); break;
                case 22: single_colour_fill_decode(); update_4(); break;
                case 23: single_colour_fill_decode(); update_8(); break;
                case 24: single_colour_fill_decode(); update_16(); break;

                case 25: four_color_fill_decode(); break;
                case 26: four_color_fill_decode(); update_4(); break;
                case 27: four_color_fill_decode(); update_8(); break;
                case 28: four_color_fill_decode(); update_16(); break;

                case 29: one_bit_tile_decode(); break;
                case 30: two_bit_tile_decode(); break;
                case 31: three_bit_tile_decode(); break;
                case 32: four_bit_tile_decode(); break;

                case 33: one_bit_tile_decode(); break;
                case 34: two_bit_tile_decode(); break;
                case 35: three_bit_tile_decode(); break;

                case 36: cross_decode(); break;
                case 37: prime_decode(); break;

                case 38: one_bank_tile_decode(); break;
                case 39: two_banks_tile_decode(); break;

                case 40: block_decode_horizontal(); break;
                case 41: block_decode_vertical(); break;
                case 42: block_decode_2(); break;
                case 43: block_decode_3(); break;

                case 44: block_bank_1_decode_horizontal(); break;
                case 45: block_bank_1_decode_vertical(); break;
                case 46: block_bank_1_decode_2(); break;
                case 47: block_bank_1_decode_3(); break;

                case 48: ro_motion_8_decode(); break;
                case 49: ro_motion_8_decode(); update_4(); break;
                case 50: ro_motion_8_decode(); update_8(); break;
                case 51: ro_motion_8_decode(); update_16(); break;

                case 52: rc_motion_8_decode(); break;
                case 53: rc_motion_8_decode(); update_4(); break;
                case 54: rc_motion_8_decode(); update_8(); break;
                case 55: rc_motion_8_decode(); update_16(); break;

                case 56: ro_motion_4_decode(); break;
                case 57: ro_motion_4_decode(); update_4(); break;
                case 58: ro_motion_4_decode(); update_8(); break;
                case 59: ro_motion_4_decode(); update_16(); break;

                case 60: rc_motion_4_decode(); break;
                case 61: rc_motion_4_decode(); update_4(); break;
                case 62: rc_motion_4_decode(); update_8(); break;
                case 63: rc_motion_4_decode(); update_16(); break;
            }
            opcode >>= 6;
            // next block
            previous_tile += 8;
            current_tile += 8;
        }
        // next line
        previous_tile += frame_width * 7;
        current_tile  += frame_width * 7;
    }
    frame_number++;
    sprintf(frame_text, "Frame: %d", frame_number);

    swap_u8_ptr(&current_buffer, &previous_buffer);

    scale_2x(state);
    screen_flip(&state->screen);
    debug_draw_text(state->screen.front_buffer, 10, 10, frame_text);
    system_blit(&state->system);
    system_flip(&state->system);
}

void print_chunk_name(chunk_t* chunk) {
    printf("[");
    for (i32 i = 0; i < 8; i++) {
        if (chunk->name[i] == ' ') break;
        printf("%c", chunk->name[i]);
    }
    printf("] (%d)\n", chunk->size);
}

void acf_play(state_t *state, const u8 *filename) {
    file_reader_t fr;
    u8* file_ptr = NULL;
    u8* data_ptr = NULL;

    if (!fropen2(&fr, (char*)filename, "rb")) {
        printf("ACF: %s can't be found !\n", filename);
        exit(1);
    }
    i32 file_size = frsize(&fr);
    file_ptr = (u8*)malloc(file_size * sizeof(u8));
    frread(&fr, file_ptr, file_size);
    frclose(&fr);

    frame_number = 0;
    current_buffer = (u8 *)malloc(frame_width * frame_height * sizeof(u8));
    previous_buffer = (u8 *)malloc(frame_width * frame_height * sizeof(u8));
    current_tile = current_buffer;

    current_chunk = (chunk_t*)file_ptr;
    chunk_t *last_chunk = (chunk_t*)(file_ptr + file_size);

    printf("\nACF: %s\n", filename);
    printf("File size: %d\n", file_size / 1024);

    while (current_chunk < last_chunk) {
        system_events(&state->system);
        if (state->system.actions[ACTION_SKIP] || state->system.quit) {
            break;
        }

        enum chunk_type_e chunk_type = CHUNK_TYPE_UNKNOWN;
        // print_chunk_name(current_chunk);
        // printf("Frame number: %d\n", frame_number);

        if (memcmp("KeyFrame", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_KEYFRAME;
        else if (memcmp("DltFrame", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_DLTFRAME;
        else if (memcmp("Format  ", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_FORMAT;
        else if (memcmp("Palette ", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_PALETTE;
        else if (memcmp("SoundBuf", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_SOUNDBUF;
        else if (memcmp("SoundFrm", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_SOUNDFRM;
        else if (memcmp("SoundEnd", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_SOUNDEND;
        else if (memcmp("End     ", current_chunk->name, 8) == 0) chunk_type = CHUNK_TYPE_END;

        if (chunk_type == CHUNK_TYPE_END) {
            break;
        }

        data_ptr = (u8 *)((u8 *)current_chunk + sizeof(chunk_t));

        // process the chunk
        switch (chunk_type) {
            case CHUNK_TYPE_FORMAT:
                format = (format_t*)(data_ptr);
                memset(current_buffer, 0, frame_width * frame_height);
                memset(previous_buffer, 0, frame_width * frame_height);
                if(!format->play_rate) {
                    format->play_rate = 12;
                }
                printf("Struct Size: %d\n", format->struct_size);
                printf("Width: %d\n", format->width);
                printf("Height: %d\n", format->height);
                printf("Frame size: %d\n", format->frame_size);
                printf("Key size: %d\n", format->key_size);
                printf("Key rate: %d\n", format->key_rate);
                printf("Play rate: %d\n", format->play_rate);
                printf("Sampling rate: %d\n", format->sampling_rate);
                printf("Sample type: %d\n", format->sample_type);
                printf("Sample flags: %d\n", format->sample_flags);
                printf("Compressor: %d\n", format->compressor);
                break;
            case CHUNK_TYPE_PALETTE:
                memccpy(palette, data_ptr, 1, current_chunk->size);
                system_set_palette(&state->system, (u8 *)palette);
                break;
            case CHUNK_TYPE_KEYFRAME:
            case CHUNK_TYPE_DLTFRAME:
                frame_data_t* frame_data = (frame_data_t*)(data_ptr);
                decompress_frame(state, frame_data);
                break;
            case CHUNK_TYPE_SOUNDBUF:
                // u8 *sound_buffer = (u8*)malloc(current_chunk->size);
                // memcpy(sound_buffer, data_ptr, current_chunk->size);
                // printf("Sound buffer size: %d\n", current_chunk->size);
                // printf("Sound buffer: %s\n", sound_buffer);
                break;
            case CHUNK_TYPE_SOUNDFRM:
                break;
            case CHUNK_TYPE_SOUNDEND:
                break;
        }
        current_chunk = (chunk_t*)((u8*)current_chunk + sizeof(chunk_t) + current_chunk->size);

        if (format) {
            system_delay_events(&state->system, 1000 / format->play_rate);
        }
    }
    free(current_buffer);
    free(file_ptr);
}
