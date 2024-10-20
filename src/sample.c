#include <stdio.h>
#include <string.h>
#include <math.h>

#include "lib/hqr.h"
#include "lib/hqr.h"

#include "sample.h"

#include "system_mixer.h"
#include "config.h"


#define HQR_RESOURCE "RESSOURC.HQR" //FIXME: shouldn't be a reference in this file


typedef struct sample_s {
    i32 playing[NUM_CHANNELS];
    i32 actors[NUM_CHANNELS];
} sample_t;

sample_t samples;


inline void sample_init() {
    memset(samples.playing, -1, sizeof(i32) * NUM_CHANNELS);
}

void sample_volume(i32 channel, i32 volume) {
    system_mixer_volume(channel, volume);
}

void sample_set_position(i32 channel_index, i32 x, i32 y, i32 z, i32 hero_x, i32 hero_y, i32 hero_z) {
    i32 distance = 0;
    // distance = abs(getDistance3D(hero_x << 9, hero_y << 8, hero_z << 9, x, y, z));
    // distance = getAverageValue(0, distance, 10000, 255);
    // if (distance > 255) {
    //     distance = 255;
    // }

    system_mixer_set_distance(channel_index, distance);
}

void sample_play(i32 index, i32 frequency, i32 repeat, i32 pan) {
    i32 sample_size = 0;
    u8* sample_ptr = NULL;
    sample_size = hqr_get_entry_alloc(&sample_ptr, HQR_RESOURCE, index);
    sample_play_position(index, sample_ptr, sample_size, frequency, repeat, 0, 0, 0, -1, 0, 0, 0);
    memory_free(sample_ptr);
}

void sample_play_ptr(i32 index, u8* sample_ptr, i32 sample_size, i32 frequency, i32 repeat, i32 pan) {
    sample_play_position(index, sample_ptr, sample_size, frequency, repeat, 0, 0, 0, -1, 0, 0, 0);
}

void sample_play_position(i32 index, u8* sample_ptr, i32 sample_size, i32 frequency, i32 repeat, i32 x, i32 y, i32 z, i32 actor_index, i32 hero_x, i32 hero_y, i32 hero_z) {
    if (!config_file.sample) {
        return;
    }

    i32 channel_index = sample_free_channel_index();

    if (channel_index != -1) {
        samples.playing[channel_index] = index;
        sample_volume(channel_index, config_file.sample_volume);

        if (actor_index != -1) {
            sample_set_position(channel_index, x, y, z, hero_x, hero_y, hero_z);
            samples.actors[channel_index] = actor_index;
        }

        if (system_mixer_play(sample_ptr, sample_size, channel_index, repeat) == -1)
            printf("Error while playing Sample %d \n", index);
    }
}

void sample_resume() {
    if (!config_file.sample) {
        return;
    }
    system_mixer_resume();
}

void sample_pause() {
    if (!config_file.sample) {
        return;
    }
    system_mixer_pause();
}

void sample_stop_all() {
    if (!config_file.sample) {
        return;
    }
    memset(samples.playing, -1, sizeof(i32) * NUM_CHANNELS);
    system_mixer_pause();
    system_mixer_free();
}

i32 sample_get_channel_actor(i32 index) {
    i32 c = 0;
    for (c = 0; c < NUM_CHANNELS; c++) {
        if (samples.actors[c] == index) {
            return c;
        }
    }
    return -1;
}

i32 sample_get_channel(i32 index) {
    i32 c = 0;
    for (c = 0; c < NUM_CHANNELS; c++) {
        if (samples.actors[c] == index) {
            return c;
        }
    }
    return -1;
}

void remove_sample_channel(i32 c) {
    samples.playing[c] = -1;
    samples.actors[c] = -1;
}

void sample_stop(i32 index) {
    if (!config_file.sample) {
        return;
    }
    i32 stopChannel = sample_get_channel(index);
    if (stopChannel != -1) {
        remove_sample_channel(stopChannel);
        system_mixer_pause_channel(stopChannel);
        system_mixer_free();
    }
}

i32 sample_is_playing_channel(i32 channel) {
    if (channel != -1) {
        if(system_mixer_is_playing(channel)) {
            return 1;
        } else {
            remove_sample_channel(channel);
        }
    }
    return 0;
}

i32 sample_is_playing(i32 index) {
    i32 channel = sample_get_channel(index);
    return sample_is_playing_channel(channel);
}

i32 sample_free_channel_index() {
    int i = 0;
    for (i = 0; i < NUM_CHANNELS; i++) {
        if (samples.playing[i] == -1) {
            return i;
        }
    }
    for (i = 0; i < NUM_CHANNELS; i++) {
        if (samples.playing[i] != -1) {
            sample_is_playing_channel(i);
        }
    }
    return -1;
}
