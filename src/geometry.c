#include <math.h>

#include "geometry.h"
#include "lib/common.h"


inline void vec2_init(vec2_t *v) {
    v->x = 0.0;
    v->y = 0.0;
}

inline vec2_t vec2_add(vec2_t a, vec2_t b) {
    return (vec2_t) {a.x + b.x, a.y + b.y};
}

inline vec2_t vec2_sub(vec2_t a, vec2_t b) {
    return (vec2_t) {a.x - b.x, a.y - b.y};
}

inline vec2_t vec2_mul(vec2_t a, vec2_t b) {
    return (vec2_t) {a.x * b.x, a.y * b.y};
}

inline vec2_t vec2_mul_scaler(vec2_t a, f32 scaler) {
    return (vec2_t) {a.x * scaler, a.y * scaler};
}

inline vec2_t vec2_div(vec2_t a, vec2_t b) {
    return (vec2_t) {a.x / b.x, a.y / b.y};
}

inline vec2_t vec2_div_scaler(vec2_t a, f32 scaler) {
    return (vec2_t) {a.x / scaler, a.y / scaler};
}

inline f32 vec2_dot(vec2_t a, vec2_t b) {
    return a.x * b.x + a.y * b.y;
}

inline f32 vec2_length(vec2_t a) {
    return sqrtf(a.x * a.x + a.y * a.y);
}

inline vec2_t vec2_normalize(vec2_t a) {
    f32 len = vec2_length(a);
    return (vec2_t) {a.x / len, a.y / len};
}

inline vec2_t vec2_rotate(vec2_t a, f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (vec2_t) {a.x * c - a.y * s, a.x * s + a.y * c};
}

inline vec2_t vec2_interpolate(vec2_t a, vec2_t b, f32 factor) {
    return (vec2_t) {a.x + (b.x - a.x) * factor, a.y + (b.y - a.y) * factor};
}

inline vec2_t vec2_reflect(vec2_t a, vec2_t normal) {
    return vec2_sub(a, vec2_mul_scaler(vec2_mul_scaler(normal, 2.0f), vec2_dot(a, normal)));
}

inline vec2_t vec2_refract(vec2_t a, vec2_t normal, f32 eta) {
    f32 k = 1.0f - eta * eta * (1.0f - vec2_dot(a, normal) * vec2_dot(a, normal));
    if (k < 0.0f) {
        return (vec2_t) {0.0f, 0.0f};
    }
    return vec2_mul_scaler(vec2_sub(vec2_mul_scaler(a, eta), normal), (eta * vec2_dot(a, normal) + sqrtf(k)));
}


inline vec3_t vec3_add(vec3_t a, vec3_t b) {
    return (vec3_t) {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline vec3_t vec3_sub(vec3_t a, vec3_t b) {
    return (vec3_t) {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline vec3_t vec3_mul(vec3_t a, vec3_t b) {
    return (vec3_t) {a.x * b.x, a.y * b.y, a.z * b.z};
}

inline vec3_t vec3_mul_scaler(vec3_t a, f32 b) {
    return (vec3_t) {a.x * b, a.y * b, a.z * b};
}

inline vec3_t vec3_div(vec3_t a, vec3_t b) {
    return (vec3_t) {a.x / b.x, a.y / b.y, a.z / b.z};
}

inline vec3_t vec3_div_scaler(vec3_t a, f32 b) {
    return (vec3_t) {a.x / b, a.y / b, a.z / b};
}

inline vec3_t vec3_cross(vec3_t a, vec3_t b) {
    return (vec3_t) {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

inline f32 vec3_dot(vec3_t a, vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline f32 vec3_length(vec3_t a) {
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline vec3_t vec3_normalize(vec3_t a) {
    f32 len = vec3_length(a);
    return (vec3_t) {a.x / len, a.y / len, a.z / len};
}

inline vec3_t vec3_rotate_x(vec3_t a, f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (vec3_t) {
        a.x,
        a.y * c - a.z * s,
        a.y * s + a.z * c
    };
}

inline vec3_t vec3_rotate_y(vec3_t a, f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (vec3_t) {
        a.x * c + a.z * s,
        a.y,
        -a.x * s + a.z * c
    };
}

inline vec3_t vec3_rotate_z(vec3_t a, f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (vec3_t) {
        a.x * c - a.y * s,
        a.x * s + a.y * c,
        a.z
    };
}

inline vec3_t vec3_interpolate(vec3_t a, vec3_t b, f32 factor) {
    return (vec3_t) {
        a.x + (b.x - a.x) * factor,
        a.y + (b.y - a.y) * factor,
        a.z + (b.z - a.z) * factor
    };
}

inline vec3_t vec3_reflect(vec3_t a, vec3_t normal) {
    return vec3_sub(a, vec3_mul_scaler(vec3_mul_scaler(normal, 2.0f), vec3_dot(a, normal)));
}

inline vec3_t vec3_refract(vec3_t a, vec3_t normal, f32 eta) {
    f32 k = 1.0f - eta * eta * (1.0f - vec3_dot(a, normal) * vec3_dot(a, normal));
    if (k < 0.0f) {
        return (vec3_t) {0.0f, 0.0f};
    }
    return vec3_mul_scaler(vec3_sub(vec3_mul_scaler(a, eta), normal), (eta * vec3_dot(a, normal) + sqrtf(k)));
}


inline mat4_t mat4_init(i32 rows, i32 cols) {
    return (mat4_t) {
        .rows = rows,
        .cols = cols,
        .m = {0},
    };
}

inline mat4_t mat4_identity() {
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = 1.0f,
        .m11 = 1.0f,
        .m22 = 1.0f,
        .m33 = 1.0f,
    };
}

inline mat4_t mat4_mul(mat4_t a, mat4_t b) {
    mat4_t c = mat4_init(a.rows, b.cols);
    for (i32 i = 0; i < a.rows; i++) {
        for (i32 j = 0; j < b.cols; j++) {
            c.m[i][j] = 0.f;
            for (i32 k = 0; k < a.cols; k++) {
                c.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return c;
}

inline vec3_t mat4_to_vec3(mat4_t a) {
    return (vec3_t) {a.m[0][0]/a.m[3][0], a.m[1][0]/a.m[3][0], a.m[2][0]/a.m[3][0]};
}

inline mat4_t vec3_to_mat4(vec3_t a) {
    return (mat4_t) {
        .rows = 4,
        .cols = 1,
        .m00 = a.x,
        .m10 = a.y,
        .m20 = a.z,
        .m30 = 1.0f,
    };
}

inline mat4_t mat4_translate(vec3_t a) {
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = 1.0f,
        .m11 = 1.0f,
        .m22 = 1.0f,
        .m33 = 1.0f,
        .m30 = a.x,
        .m31 = a.y,
        .m32 = a.z,
    };
}

inline mat4_t mat4_scale(vec3_t a) {
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = a.x,
        .m11 = a.y,
        .m22 = a.z,
        .m33 = 1.0f,
    };
}

inline mat4_t mat4_rotate_x(f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = 1.0f,
        .m11 = c,
        .m12 = -s,
        .m21 = s,
        .m22 = c,
        .m33 = 1.0f,
    };
}

inline mat4_t mat4_rotate_y(f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = c,
        .m02 = s,
        .m11 = 1.0f,
        .m20 = -s,
        .m22 = c,
        .m33 = 1.0f,
    };
}

inline mat4_t mat4_rotate_z(f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = c,
        .m01 = -s,
        .m10 = s,
        .m11 = c,
        .m22 = 1.0f,
        .m33 = 1.0f,
    };
}

inline mat4_t mat4_transpose(mat4_t a) {
    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = a.m00,
        .m01 = a.m10,
        .m02 = a.m20,
        .m03 = a.m30,
        .m10 = a.m01,
        .m11 = a.m11,
        .m12 = a.m21,
        .m13 = a.m31,
        .m20 = a.m02,
        .m21 = a.m12,
        .m22 = a.m22,
        .m23 = a.m32,
        .m30 = a.m03,
        .m31 = a.m13,
        .m32 = a.m23,
        .m33 = a.m33,
    };
}

inline mat4_t mat4_inverse(mat4_t a) {
    f32 s0 = a.m[0][0] * a.m[1][1] - a.m[1][0] * a.m[0][1];
    f32 s1 = a.m[0][0] * a.m[1][2] - a.m[1][0] * a.m[0][2];
    f32 s2 = a.m[0][0] * a.m[1][3] - a.m[1][0] * a.m[0][3];
    f32 s3 = a.m[0][1] * a.m[1][2] - a.m[1][1] * a.m[0][2];
    f32 s4 = a.m[0][1] * a.m[1][3] - a.m[1][1] * a.m[0][3];
    f32 s5 = a.m[0][2] * a.m[1][3] - a.m[1][2] * a.m[0][3];

    f32 c5 = a.m[2][2] * a.m[3][3] - a.m[3][2] * a.m[2][3];
    f32 c4 = a.m[2][1] * a.m[3][3] - a.m[3][1] * a.m[2][3];
    f32 c3 = a.m[2][1] * a.m[3][2] - a.m[3][1] * a.m[2][2];
    f32 c2 = a.m[2][0] * a.m[3][3] - a.m[3][0] * a.m[2][3];
    f32 c1 = a.m[2][0] * a.m[3][2] - a.m[3][0] * a.m[2][2];
    f32 c0 = a.m[2][0] * a.m[3][1] - a.m[3][0] * a.m[2][1];

    f32 invdet = 1.0f / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    return (mat4_t) {
        .rows = 4,
        .cols = 4,
        .m00 = (a.m[1][1] * c5 - a.m[1][2] * c4 + a.m[1][3] * c3) * invdet,
        .m01 = (-a.m[0][1] * c5 + a.m[0][2] * c4 - a.m[0][3] * c3) * invdet,
        .m02 = (a.m[3][1] * s5 - a.m[3][2] * s4 + a.m[3][3] * s3) * invdet,
        .m03 = (-a.m[2][1] * s5 + a.m[2][2] * s4 - a.m[2][3] * s3) * invdet,
        .m10 = (-a.m[1][0] * c5 + a.m[1][2] * c2 - a.m[1][3] * c1) * invdet,
        .m11 = (a.m[0][0] * c5 - a.m[0][2] * c2 + a.m[0][3] * c1) * invdet,
        .m12 = (-a.m[3][0] * s5 + a.m[3][2] * s2 - a.m[3][3] * s1) * invdet,
        .m13 = (a.m[2][0] * s5 - a.m[2][2] * s2 + a.m[2][3] * s1) * invdet,
        .m20 = (a.m[1][0] * c4 - a.m[1][1] * c2 + a.m[1][3] * c0) * invdet,
        .m21 = (-a.m[0][0] * c4 + a.m[0][1] * c2 - a.m[0][3] * c0) * invdet,
        .m22 = (a.m[3][0] * s4 - a.m[3][1] * s2 + a.m[3][3] * s0) * invdet,
        .m23 = (-a.m[2][0] * s4 + a.m[2][1] * s2 - a.m[2][3] * s0) * invdet,
        .m30 = (-a.m[1][0] * c3 + a.m[1][1] * c1 - a.m[1][2] * c0) * invdet,
        .m31 = (a.m[0][0] * c3 - a.m[0][1] * c1 + a.m[0][2] * c0) * invdet,
        .m32 = (-a.m[3][0] * s3 + a.m[3][1] * s1 - a.m[3][2] * s0) * invdet,
        .m33 = (a.m[2][0] * s3 - a.m[2][1] * s1 + a.m[2][2] * s0) * invdet,
    };
}

inline void mat4_print(mat4_t a) {
    printf("mat4_t {\n");
    for (i32 i = 0; i < a.rows; i++) {
        printf("    { ");
        for (i32 j = 0; j < a.cols; j++) {
            printf("%f, ", a.m[i][j]);
        }
        printf("},\n");
    }
    printf("}\n");
}


inline void swap_xor(i32 *a, i32 *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

inline void swap_vec2(vec2_t *a, vec2_t *b) {
    vec2_t temp = *b;
    *b = *a;
    *a = temp;
}

inline void swap_vec3(vec3_t *a, vec3_t *b) {
    vec3_t temp = *b;
    *b = *a;
    *a = temp;
}
