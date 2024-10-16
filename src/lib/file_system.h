#pragma once

#include "common.h"

bool file_exists(const char* path);
i32 file_size(const char* path);

FILE* file_open(const char* path, const char* mode);
void file_close(FILE* file);
void file_seek(FILE* file, i32 offset, i32 origin);

void file_read_buffer(FILE* file, void* buffer, i32 size);

u8 file_read_i8(FILE* file);
u16 file_read_i16(FILE* file);
u32 file_read_i32(FILE* file);

i8 file_read_u8(FILE* file);
i16 file_read_u16(FILE* file);
i32 file_read_u32(FILE* file);
