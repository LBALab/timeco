#ifndef MUSIC_H
#define MUSIC_H

#include "lib/common.h"


extern i32 music_index;


void music_volume(i32 volume);

void music_play_midi(i32 stage, i32 run, i32 midi_index, i32 loop);
void music_stop_midi();
void music_stop();

void music_play_track(i32 track);
void music_stop_track();

void music_play_track_mp3(i32 track);
void music_stop_track_mp3();

#endif
