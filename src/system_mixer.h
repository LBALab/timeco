
#ifndef SYSTEM_MIXER_H
#define SYSTEM_MIXER_H

#include "lib/common.h"


void system_mixer_init(i32 sound_config);
void system_mixer_close();

void system_mixer_volume(i32 channel, i32 volume);
i32 system_mixer_is_playing(i32 channel);

void system_mixer_set_distance(i32 channel_index, i32 distance);

void system_mixer_load(u8 *sample_ptr, i32 samples_size);
void system_mixer_free();
i32 system_mixer_play(u8 *sample_ptr, i32 samples_size, i32 channel_index, i32 loop);

void system_mixer_resume();
void system_mixer_pause();
void system_mixer_pause_channel(i32 channel_index);

void system_mixer_music_fade_in(i32 loop, i32 ms);
void system_mixer_music_volume(i32 volume);
void system_mixer_music_fade_out(i32 ms);

void system_mixer_load_music(u8 *music_ptr, i32 music_size);
i32 system_mixer_free_music();
i32 system_mixer_play_music(u8 *music_ptr, i32 music_size, i32 loop);
i32 system_mixer_play_music_mp3(c8 *music_file);
void system_mixer_stop_music_mp3();

#endif
