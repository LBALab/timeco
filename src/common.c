#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // memcpy

#include "common.h"


// i32 total_memory_used = 0;


inline void* memory_alloc(i32 size) {
    void* ptr = (void *)malloc(size);
    // total_memory_used += size; // TODO use hash table instead
    // #ifdef MEM_DEBUG
    // print("memory_alloc(%d) = %p (total: %d)\n", size, ptr, total_memory_used);
    // #endif
    return ptr;
}

inline void* memory_calloc(i32 size) {
    void* ptr = (void *)calloc(1, size);
    // total_memory_used += size; // TODO use hash table instead
    // #ifdef MEM_DEBUG
    // print("memory_alloc(%d) = %p (total: %d)\n", size, ptr, total_memory_used);
    // #endif
    return ptr;
}

inline void memory_free(void* ptr) {
    // total_memory_used += sizeof(ptr); // TODO use hash table instead
    free(ptr);
}

inline void memory_copy(void* dest, void* src, i32 size) {
    memcpy(dest, src, size);
}

inline void array_init(array_s *array, i32 capacity) {
    array->data = memory_alloc(capacity);
    array->size = 0;
    array->capacity = capacity;
};

inline void array_release(array_s *array) {
    memory_free(array->data);
};

inline void array_push(array_s *array, void* item) {
    void *dest = realloc(array->data, array->size + sizeof(item));
    if (dest) {
        array->data = dest;
        array->size += sizeof(item);
    }
};

inline i32 abs(i32 value) {
    return value < 0 ? -value : value;
}

inline void swap(i32 *a, i32 *b) {
    i32 temp = *b;
    *b = *a;
    *a = temp;
}

inline void swap_u8(u8 *a, u8 *b) {
    u8 temp = *b;
    *b = *a;
    *a = temp;
}

inline f32 min(f32 a, f32 b) {
    return a < b ? a : b;
}

inline f32 max(f32 a, f32 b) {
    return a > b ? a : b;
}
