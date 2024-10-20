#ifndef SAMPLE_H
#define SAMPLE_H

#include "lib/common.h"


#define NUM_CHANNELS 32

void sample_init();

i32 sample_is_playing(i32 index);

void sample_play(i32 index, i32 frequency, i32 repeat, i32 pan);
void sample_play_position(i32 index, i32 frequency, i32 repeat, i32 x, i32 y, i32 z, i32 actor_index, i32 hero_x, i32 hero_y, i32 hero_z);
void sample_pause();
void sample_resume();
void sample_stop_all();
void sample_stop(i32 index);
void sample_volume(i32 channel, i32 volume);
void sample_set_position(i32 channelIdx, i32 x, i32 y, i32 z, i32 hero_x, i32 hero_y, i32 hero_z);

i32 sample_get_channel_actor(i32 index);
i32 sample_get_channel(i32 index);
i32 sample_free_channel_index();
void remove_sample_channel(i32 index);

#endif
