#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hqr.h"
#include "utils/filereader.h"


file_reader_t fr;


void hqr_entry_decompress(u8 * dst, u8 * src, i32 decompsize, i32 mode) {
    u8 b;
    i32 lenght, d, i;
    u16 offset;
    u8 *ptr;

    do {
        b = *(src++);
        for (d = 0; d < 8; d++) {
            if (!(b & (1 << d))) {
                offset = *(u16*)(src);
                src += 2;
                lenght = (offset & 0x0F) + (mode + 1);
                ptr = dst - (offset >> 4) - 1;
                for (i = 0; i < lenght; i++)
                    *(dst++) = *(ptr++);
            } else {
                lenght = 1;
                *(dst++) = *(src++);
            }
            decompsize -= lenght;
            if (decompsize <= 0)
                return;
        }
    } while (decompsize);
}

void hqr_entry_decompress_lz(u8 * dst, u8 * src, i32 decompsize, i32 mode) {
    u16 offset;
    i32 lenght;
    u8 *ptr;

    while (decompsize > 0) {
        u8 bits;
        u8 type = *(src++);
        for (bits = 1; bits != 0; bits <<= 1) {
            if (!(type&bits)) {
                offset = *(u16*)(src);
                src += 2;
                lenght = (offset & 0x0F) + (mode + 1);
                ptr = dst - (offset >> 4) - 1;
                if (offset == 0) {
                    memset(dst, *ptr, lenght);
                } else {
                    if ((ptr + lenght) >= dst) {
                        i32 n;
                        u8 *tmp = dst;
                        for (n = 0; n < lenght; n++)
                            *tmp++ = *ptr++;
                    } else {
                        memcpy(dst, ptr, lenght);
                    }
                }
                dst += lenght;
            } else {
                lenght = 1;
                *(dst++) = *(src++);
            }
            decompsize -= lenght;
            if (decompsize <= 0)
                return;
        }
    }
}

i32 hqr_get_entry(u8 * ptr, c8 *filename, i32 index) {
    u32 headerSize;
    u32 offsetToData;
    u32 realSize;
    u32 compSize;
    u16 mode;

    if (!filename)
        return 0;

    if (!fropen2(&fr, (char*)filename, "rb"))
        printf("HQR: %s can't be found !\n", filename);

    frread(&fr, &headerSize, 4);

    if ((u32)index >= headerSize / 4) {
        printf("\nHQR WARNING: Invalid entry index!!\n");
        frclose(&fr);
        return 0;
    }

    frseek(&fr, index*4);
    frread(&fr, &offsetToData, 4);

    frseek(&fr, offsetToData);
    frread(&fr, &realSize, 4);
    frread(&fr, &compSize, 4);
    frread(&fr, &mode, 2);

    if (!ptr)
        ptr = (u8*)malloc(realSize);

    if (!ptr) {
        printf("\nHQR WARNING: Unable to allocate memory!!\n");
        frclose(&fr);
        return 0;
    }

    // uncompressed
    if (mode == 0) {
        frread(&fr, ptr, realSize);
    }
    // compressed: modes (1 & 2)
    else if (mode == 1 || mode == 2) {
        u8* compDataPtr = 0;
        compDataPtr = (u8*)malloc(compSize);
        frread(&fr, compDataPtr, compSize);
        hqr_entry_decompress(ptr, compDataPtr, realSize, mode);
        free(compDataPtr);
    }

    frclose(&fr);

    return realSize;
}

int hqr_get_entry_size(c8 *filename, i32 index) {
    u32 headerSize;
    u32 offsetToData;
    u32 realSize;

    if (!filename)
        return 0;

    if (!fropen2(&fr, (char*)filename, "rb")) {
        printf("HQR: %s can't be found !\n", filename);
        exit(1);
    }

    frread(&fr, &headerSize, 4);

    if ((u32)index >= headerSize / 4) {
        printf("\nHQR WARNING: Invalid entry index!!\n");
        frclose(&fr);
        return 0;
    }

    frseek(&fr, index*4);
    frread(&fr, &offsetToData, 4);

    frseek(&fr, offsetToData);
    frread(&fr, &realSize, 4);

    frclose(&fr);

    return realSize;
}

int hqr_get_num_entries(c8 *filename) {
    u32 headerSize;

    if (!filename)
        return 0;

    if (!fropen2(&fr, (char*)filename, "rb")) {
        printf("HQR: %s can't be found !\n", filename);
        exit(1);
    }

    frread(&fr, &headerSize, 4);

    return headerSize / 4;
}

i32 hqr_get_entry_alloc(u8 ** ptr, c8 *filename, i32 index) {
    i32 size;
    size = hqr_get_entry_size(filename, index);

    *ptr = (u8*)malloc(size * sizeof(u8));
    if (!*ptr) {
        printf("HQR WARNING: unable to allocate entry memory!!\n");
        return 0;
    }
    hqr_get_entry(*ptr, filename, index);

    return size;
}
