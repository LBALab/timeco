#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#ifdef DEBUG
#define printf printf
#else
#define printf(...)
#endif

#define FALSE 0
#define TRUE 1


typedef char c8;
typedef bool b8;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float  f32;
typedef double f64;

extern i32 total_memory_used;

typedef struct {
    void* data;
    i32 size;
    i32 capacity;
} array_s;


void* memory_alloc(i32 size);
void* memory_calloc(i32 size);
void memory_free(void* ptr);
void memory_copy(void* dest, void* src, i32 size);

void array_init(array_s *array, i32 capacity);
void array_release(array_s *array);
void array_push(array_s *array, void* item);

i32 abs(i32 value);
void swap(i32 *a, i32 *b);
void swap_u8(u8 *a, u8 *b);
f32 min(f32 a, f32 b);
f32 max(f32 a, f32 b);

u16 read_u16(const u8* ptr);
i16 read_s16(const u8* ptr);
u32 read_u32(const u8* ptr, int skip);
i16 read_xy_offset(const u8* ptr, int stride);
