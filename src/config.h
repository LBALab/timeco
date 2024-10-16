
#ifndef CONFIG_H
#define CONFIG_H

#include "lib/common.h"

typedef struct config_file_s {
    i32 full_screen;
    i32 cross_fade;
    i32 debug;
    i32 quit;
    i32 version;
    i8 language[10];
    i32 difficulty;
    i32 sample_volume;
    i32 music;
    i32 resolution;
} config_file_t;

extern config_file_t config_file;

void config_init();

#endif
