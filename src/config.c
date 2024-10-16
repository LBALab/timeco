#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lib/common.h"
#include "lib/file_reader.h"
#include "lib/fcaseopen.h"

#include "config.h"


#define DEFAULT_FRAMES_PER_SECOND 20;


const c8* CONFIG_FILENAME = "timeco.def";

c8 CFGList[][22] = {
    "FullScreen:",
    "CrossFade:",
    "Fps:",
    "Debug:",
    //
    "Language:",
    "Version:",
    "CompressSave:",
    "Texture:",
    "DoubleBuffer:",
    "ReverseStereo:",
    "NumPlayer:",
    "Difficulty:",
    "SampleVolume:",
    "Music:",
    "Resolution:",
    "Data:",
    "OS:",
    "Input0:",
    "Mask0:",
    "Input1:",
    "Mask1:",
    "Input2:",
    "Mask2:",
    "Input3:",
    "Mask3:",
    "Input4:",
    "Mask4:",
    "Input5:",
    "Mask5:",
    "Input6:",
    "Mask6:",
    "Input7:",
    "Mask7:",
    "Input8:",
    "Mask8:",
    "Input9:",
    "Mask9:",
    "Input10:",
    "Mask10:",
};

config_file_t config_file;

int config_get_type_index(c8* lineBuffer) {
    i32 i;
    char buffer[256];
    char* ptr;

    strcpy(buffer, lineBuffer);

    ptr = strchr(buffer, ' ');

    if (ptr) {
        *ptr = 0;
    }

    for (i = 0; i < (sizeof(CFGList) / 22); i++) {
        if (strlen(CFGList[i])) {
            if (!strcmp(CFGList[i], buffer)) {
                return i;
            }
        }
    }

    return -1;
}


void config_init() {
    i32 cfgtype = -1;
    c8 buffer[256];
    // c8 tmp[16];
    FILE *fd;

    fd = fcaseopen(CONFIG_FILENAME, "rb");
    if (!fd)
        printf("Error: Can't find config file %s\n", CONFIG_FILENAME);

    // make sure it quit when it reaches the end of file
    while (fgets(buffer, 256, fd) != NULL) {
        *strchr(buffer, 0x0D0A) = 0;
        cfgtype = config_get_type_index(buffer);
        if (cfgtype != -1) {
            switch (cfgtype) {
            case 0:
                sscanf(buffer, "Version: %d", &config_file.version);
            case 1:
                sscanf(buffer, "Language: %s", config_file.language);
                break;
            // case 2:
            //     sscanf(buffer, "CompressSave: %s", tmp);
            //     break;
            // case 19:
            //     sscanf(buffer, "SampleVolume: %d", &config_file.sample_volume);
            //     break;

            // case 26:
            //     sscanf(buffer, "FullScreen: %d", &config_file.full_screen);
            //     break;
            // case 28:
            //     sscanf(buffer, "Music: %d", &config_file.music);
            //     break;
            // case 30:
            //     sscanf(buffer, "CrossFade: %d", &config_file.cross_fade);
            //     break;
            // case 31:
            //     sscanf(buffer, "Fps: %d", &config_file.fps);
            //     break;
            // case 32:
            //     sscanf(buffer, "Debug: %d", &config_file.debug);
            //     break;
            }
        }
    }

    if (!config_file.fps)
        config_file.fps = DEFAULT_FRAMES_PER_SECOND;

    config_file.debug = 1;

    fclose(fd);
}
