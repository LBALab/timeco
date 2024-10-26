#include <ctype.h>

#include "file_reader.h"
#include "fcaseopen.h"


// inline void frfeed(file_reader_t* fr) {
//     fread(fr->buffer, BUFFER_SIZE, 1, fr->fd);
//     fr->bufferPos = 0;
// }

void frread(file_reader_t* fr, void* destPtr, u32 size) {
    fread(destPtr, size, 1, fr->fd);
    // fr->bufferPos = 0;
}

/*void frread(file_reader_t* fr, void* destPtr, u32 size) {
    if (BUFFER_SIZE - fr->bufferPos >= size) {
        memcpy(destPtr, &fr->buffer[fr->bufferPos], size);
        fr->bufferPos += size;
    } else {
        // feed what we can
        u8* tempPtr = (u8*)destPtr;
        memcpy(tempPtr, &fr->buffer[fr->bufferPos], BUFFER_SIZE - fr->bufferPos);
        tempPtr += BUFFER_SIZE - fr->bufferPos;
        size -= BUFFER_SIZE - fr->bufferPos;

        // feed the rest
        do {
            fr->currSector++;
            frfeed(fr);
            if (size >= BUFFER_SIZE) {
                memcpy(tempPtr, fr->buffer, BUFFER_SIZE);
                tempPtr += BUFFER_SIZE;
                size -= BUFFER_SIZE;
            } else {
                memcpy(tempPtr, fr->buffer, size);
                fr->bufferPos += size;
                size = 0;
            }
        } while (size > 0);
    }
}*/

void frseek(file_reader_t* fr, u32 seekPosition) {
    // u32 sectorToSeek;

    // sectorToSeek = seekPosition / 2048;

    fseek(fr->fd, seekPosition, SEEK_SET); //sectorToSeek * 2048, SEEK_SET);

    // fr->currSector = sectorToSeek;
    // frfeed(fr);
    // fr->bufferPos = (seekPosition - (sectorToSeek * 2048));
}

i32 fropen2(file_reader_t* fr, char* filename, const char* mode) {
    fr->fd = fcaseopen(filename, mode);

    if (fr->fd) {
        // fr->currSector = 0;
        // frfeed(fr);
        return 1;
    }

    return 0;
}

inline void frwrite(file_reader_t* fr, void* destPtr, u32 size, u32 count) {
    fwrite(destPtr, size, count, fr->fd);
}

inline void frclose(file_reader_t* fr) {
    fclose(fr->fd);
}

i32 frsize(file_reader_t* fr) {
    fseek(fr->fd, 0, SEEK_END);
    i32 size = ftell(fr->fd);
    fseek(fr->fd, 0, SEEK_SET);
    return size;
}
