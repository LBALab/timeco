#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"


#define SECTORS_IN_BUFFER (3)
#define BUFFER_SIZE (2048*SECTORS_IN_BUFFER)


typedef struct file_reader_s {
    FILE* fd;
    // u8 buffer[BUFFER_SIZE];
    // u32 bufferPos;
    // u32 currSector;
} file_reader_t;


// void frfeed(file_reader_t* fr);
void frread(file_reader_t* fr, void* destPtr, u32 size);
void frseek(file_reader_t* fr, u32 seekPosition);
i32 fropen2(file_reader_t* fr, char* filename, const char* mode);
void frwrite(file_reader_t* fr, void* destPtr, u32 size, u32 count);
void frclose(file_reader_t* fr);
i32 frsize(file_reader_t* fr);

#endif
