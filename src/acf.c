#include <string.h>

#include "acf.h"
#include "lib/common.h"

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

typedef struct {
    u32 biggest_frame_size;
    u8 frame_size_in_sectors;
} frame_len_t;

typedef struct {
    u32 colour_offset;
    u8 opcodes[30];
} frame_data_t;

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

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
} palette_entry_t;

typedef struct {
    palette_entry_t entries[256];
} palette_t;

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

chunk_t* current_chunk = NULL;
format_t* format = NULL;
palette_t* palette = NULL;
frame_len_t* frame_len = NULL;
camera_t* camera = NULL;

u8* previous_buffer = NULL;
u8* previous_frame_buffer = NULL;
u8* previous_tile = NULL;
u8* current_buffer = NULL;
u8* current_tile = NULL;

u8* aligned_stream = NULL;
u8* unaligned_stream = NULL;



void set_pixel(i32 x, i32 y, u8 colour) {
    current_tile[x + (y * frame_width)] = colour;
}

// 3 bytes (6 bits x 4) for the position, 4 bytes for colors
void update_4() {
    u32 value = *(u32*)unaligned_stream;	// Que 3 octets int‚ressants (Little Endian)
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
                set_pixel(x,y, *unaligned_stream++);
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
    u8 colorTile = *unaligned_stream++;
    for (i32 y = 0; y < 8; y++) {
        memset(current_tile + y * frame_width, colorTile, 8);
    }
}

// Load four bytes, one for each quadrant of the tile
void four_color_fill_decode() {
    u8 colorTopLeft = *aligned_stream++;
    u8 colorTopRight = *aligned_stream++;
    u8 colorBottomLeft = *aligned_stream++;
    u8 colorBottomRight = *aligned_stream++;

    for (i32 y = 0; y < 4; y++) {
      memset(current_tile + y * frame_width, colorTopLeft, 4);
      memset(current_tile + y * frame_width + 4, colorTopRight, 4);
      memset(current_tile + (y + 4) * frame_width, colorBottomLeft, 4);
      memset(current_tile + (y + 4) * frame_width + 4, colorBottomRight, 4);
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
    i32 prime_color = *unaligned_stream++;
    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                set_pixel(x, y, *unaligned_stream++);
            } else {
                set_pixel(x, y, prime_color);
            }
            a >>= 1;
        }
    }
}

// All 64 colors to directly copy to the buffer. No trick of any kind
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
                set_pixel(x,y, bank + ((*aligned_stream++) >> 4));
            } else {
                set_pixel(x,y, bank + ((*aligned_stream) & 15));
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
        u32 part1 = *(i32*)aligned_stream;		// On r‚cupŠre ainsi 5 octets...
        u32 part2 = *(i32*)(aligned_stream + 4);
        aligned_stream += 5;
        for (u32 x = 0; x < 8; x++) {
            set_pixel(x, y, bank[(part1 & 16) >> 4] + (part1 & 15));   // Bit 4: Banque … utiliser / Bits 0-3:Couleur
            part1 >>= 5;
            part1 |= (part2 << 27);
            part2 >>= 5;
        }
    }
}

void block_decode_horizontal() {
    u8 last_color = 0;

    for (u32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (u32 x = 0; x < 8; x++) {
            if (a & 1) {
                last_color = *unaligned_stream++;
            }
            a >>= 1;
            set_pixel(x, y, last_color);
        }
    }
}

void block_decode_vertical() {
    u8 last_color = 0;

    for (i32 x = 0; x < 8; x++) {
        u8 a = *aligned_stream++;
        for (i32 y = 0; y < 8; y++) {
            if (a & 1) {
                last_color = *unaligned_stream++;
            }
            a >>= 1;
            set_pixel(x, y, last_color);
        }
    }
}

void block_decode_2() {
    u8 last_color = 0;
    u32* offsets = diagonal_offsets_1;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                last_color = *unaligned_stream++;
            }
            a >>= 1;
            current_tile[*offsets++] = last_color;
        }
    }
}

void block_decode_3() {
    u8 last_color = 0;
    u32* offsets = diagonal_offsets_2;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                last_color = *unaligned_stream++;
            }
            a >>= 1;
            current_tile[*offsets++] = last_color;
        }
    }
}

void block_bank_1_decode_horizontal() {
    u8 last_color = 0;
    u8 bank = (*unaligned_stream) << 4;	// R‚cupŠre la banque
    u8 flag = 1;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                if (flag) {
                    last_color = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_color = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            set_pixel(x, y, bank + last_color);
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void block_bank_1_decode_vertical() {
    u8 last_color = 0;
    u8 bank = (*unaligned_stream) << 4;	// get the bank back
    u8 flag = 1;

    for (i32 x = 0; x < 8; x++) {
        u8 a = *aligned_stream++;
        for (i32 y = 0; y < 8; y++) {
            if (a & 1) {
                if (flag) {
                    last_color = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_color = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            set_pixel(x, y, bank + last_color);
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void block_bank_1_decode_2() {
    u8 last_color = 0;
    u8 bank = (*unaligned_stream) << 4;	// R‚cupŠre la banque
    u8 flag = 1;
    u32* offsets = diagonal_offsets_1;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                if (flag) {
                    last_color = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_color = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            current_tile[*offsets++] = bank + last_color;
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void block_bank_1_decode_3() {
    u8 last_color = 0;
    u8 bank = (*unaligned_stream) << 4;	// Get the bank number
    u8 flag = 1;
    u32* offsets = diagonal_offsets_2;

    for (i32 y = 0; y < 8; y++) {
        u8 a = *aligned_stream++;
        for (i32 x = 0; x < 8; x++) {
            if (a & 1) {
                if (flag) {
                    last_color = (*unaligned_stream) >> 4;
                    flag = 0;
                    unaligned_stream++;
                } else {
                    last_color = (*unaligned_stream) & 15;
                    flag++;
                }
            }
            a >>= 1;
            current_tile[*offsets++] = bank + last_color;
        }
    }
    if (flag) {
        unaligned_stream++;
    }
}

void acf_play(const u8 *filename) {

}
