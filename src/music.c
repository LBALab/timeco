#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/xmidi.h"
#include "lib/hqr.h"

#include "music.h"
#include "system_mixer.h"
#include "system.h"
#include "config.h"


#define FADE_MS			    500


i32 music_index;
u8 * midi_ptr;


void music_volume(i32 volume) {
    system_mixer_music_volume(volume);
}

void music_fade_in(i32 loops, i32 ms) {
    system_mixer_music_fade_in(loops, ms);
    music_volume(config_file.music_volume);
}

void music_fade_out(i32 ms) {
    system_mixer_music_fade_out(ms);
    music_volume(config_file.music_volume);
}

void music_play_track(i32 track) {
    if (!config_file.music) {
        return;
    }
    if (track == music_index) {
        return;
    }
    music_index = track;
    music_stop();
    music_play_track_mp3(track);
}

void music_stop_track() {
    if (!config_file.music) {
        return;
    }
    music_fade_out(FADE_MS);
    system_mixer_stop_music_mp3();
}

void music_play_midi(i32 stage, i32 run, i32 midi_index, i32 loop) {
    u8* dos_midi_ptr;
    i32 midi_size;
    c8 filename[256];

    if (!config_file.music) {
        return;
    }
    if (midi_index == music_index) {
        return;
    }

    music_stop();
    music_index = midi_index;

    if (midi_ptr) {
        music_fade_out(FADE_MS / 2);
        music_stop_midi();
    }

    sprintf(filename, "stage0%d/run%d/scene.hqr", stage, run);
    midi_size = hqr_get_entry_alloc(&midi_ptr, filename, midi_index);

    midi_size = convert_to_midi(midi_ptr, midi_size, &dos_midi_ptr);
    free(midi_ptr);
    midi_ptr = dos_midi_ptr;

    music_fade_in(1, FADE_MS);
    music_volume(config_file.music_volume);

    if (system_mixer_play_music(midi_ptr, midi_size, loop) == -1) {
        printf("Error while playing music: %d \n", midi_index);
    }  else if (config_file.debug) {
        printf("Playing mini: %s\n", filename);
    }
}

void music_stop_midi() {
    if (!config_file.music) {
        return;
    }
    if(system_mixer_free_music()) {
        if (midi_ptr != NULL) {
            free(midi_ptr);
        }
    }
}

void music_stop() {
    music_stop_track();
    music_stop_midi();
}

void music_play_track_mp3(i32 track) {
    c8 musfile[256];
    if (config_file.music == 1) {
        sprintf(musfile, "music/Track_0%d.mp3", track);
    } else {
        sprintf(musfile, "music/Track_0%d.ogg", track);
    }
    system_mixer_stop_music_mp3();
    system_mixer_music_fade_in(1, FADE_MS);
    music_volume(config_file.music_volume);
    if (system_mixer_play_music_mp3(musfile) == -1) {
        printf("Error while playing music: %d \n", track);
    } else if (config_file.debug) {
        if (config_file.music == 1) {
            printf("Playing track (MP3): %s\n", musfile);
        } else {
            printf("Playing track (OGG): %s\n", musfile);
        }
    }
}
