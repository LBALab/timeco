#pragma once

#include "lib/common.h"


typedef struct {
    union {
        struct {
            f32 x, y;
        };
        struct {
            f32 u, v;
        };
        f32 raw[2];
    };
} vec2_t;

typedef struct {
    union {
        struct {
            f32 x, y, z;
        };
        struct {
            f32 ivert, iuv, inorm;
        };
        f32 raw[3];
    };
} vec3_t;

typedef struct {
    i32 rows;
    i32 cols;
    union {
        f32 m[4][4];
        struct {
            f32 m00, m01, m02, m03;
            f32 m10, m11, m12, m13;
            f32 m20, m21, m22, m23;
            f32 m30, m31, m32, m33;
        };
    };
} mat4_t;


void vec2_init(vec2_t *v);

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);

vec2_t vec2_mul(vec2_t a, vec2_t b);
vec2_t vec2_mul_scaler(vec2_t a, f32 scaler);

vec2_t vec2_div(vec2_t a, vec2_t b);
vec2_t vec2_div_scaler(vec2_t a, f32 scaler);

f32 vec2_dot(vec2_t a, vec2_t b);

f32 vec2_length(vec2_t a);
vec2_t vec2_normalize(vec2_t a);

vec2_t vec2_interpolate(vec2_t a, vec2_t b, f32 factor);
vec2_t vec2_reflect(vec2_t a, vec2_t normal);
vec2_t vec2_refract(vec2_t a, vec2_t normal, f32 eta);

vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);

vec3_t vec3_mul(vec3_t a, vec3_t b);
vec3_t vec3_mul_scaler(vec3_t a, f32 b);

vec3_t vec3_div(vec3_t a, vec3_t b);
vec3_t vec3_div_scaler(vec3_t a, f32 b);

vec3_t vec3_cross(vec3_t a, vec3_t b);
f32 vec3_dot(vec3_t a, vec3_t b);

f32 vec3_length(vec3_t a);
vec3_t vec3_normalize(vec3_t a);

vec3_t vec3_rotate_x(vec3_t a, f32 angle);
vec3_t vec3_rotate_y(vec3_t a, f32 angle);
vec3_t vec3_rotate_z(vec3_t a, f32 angle);

vec3_t vec3_interpolate(vec3_t a, vec3_t b, f32 factor);
vec3_t vec3_reflect(vec3_t a, vec3_t normal);
vec3_t vec3_refract(vec3_t a, vec3_t normal, f32 eta);

mat4_t mat4_init(i32 rows, i32 cols);
mat4_t mat4_identity();
mat4_t mat4_mul(mat4_t a, mat4_t b);

vec3_t mat4_to_vec3(mat4_t a);
mat4_t vec3_to_mat4(vec3_t a);

mat4_t mat4_translate(vec3_t a);
mat4_t mat4_scale(vec3_t a);

mat4_t mat4_rotate_x(f32 angle);
mat4_t mat4_rotate_y(f32 angle);
mat4_t mat4_rotate_z(f32 angle);

mat4_t mat4_transpose(mat4_t a);
mat4_t mat4_inverse(mat4_t a);

void mat4_print(mat4_t a);

void swap_xor(i32 *a, i32 *b);
void swap_vec2(vec2_t *a, vec2_t *b);
void swap_vec3(vec3_t *a, vec3_t *b);
