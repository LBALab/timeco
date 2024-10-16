#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "system_mixer.h"


#define ORIGINAL_GAME_FREQUENCY		11025
#define HIGH_QUALITY_FREQUENCY		44100
#define NUM_CD_TRACKS	10


Mix_Chunk *chunk;
Mix_Music *current_track;


void system_mixer_init(i32 sound_config) {
    SDL_AudioSpec spec;
    spec.freq = 22050;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;

    if (!Mix_OpenAudio(0, &spec)) {
        printf("Mix_OpenAudio: %s\n", SDL_GetError());
        exit(1);
    }
    
    // if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
    //     printf("Mix_Init: %s\n", SDL_GetError());
    //     exit(1);
    // }

    Mix_AllocateChannels(32);
}

inline void system_mixer_close() {
    Mix_CloseAudio();
}

inline void system_mixer_volume(i32 channel, i32 volume) {
    Mix_Volume(channel, volume / 2);
}

inline i32 system_mixer_is_playing(i32 channel) {
    return Mix_Playing(channel);
}

inline void system_mixer_set_distance(i32 channel_index, i32 distance) {
    Mix_SetDistance(channel_index, distance);
}

inline void system_mixer_load(u8 *sample_ptr, i32 samples_size) {
    SDL_IOStream *rw = SDL_IOFromMem(sample_ptr, samples_size);
    chunk = Mix_LoadWAV_IO(rw, 1);
}

inline void system_mixer_free() {
    Mix_FreeChunk(chunk);
    chunk = NULL;
}

i32 system_mixer_play(u8 *sample_ptr, i32 samples_size, i32 channel_index, i32 loop) {
    system_mixer_load(sample_ptr, samples_size);
    return Mix_PlayChannel(channel_index, chunk, 0);
}

inline void system_mixer_resume() {
    Mix_Resume(-1);
}

inline void system_mixer_pause() {
    Mix_HaltChannel(-1);
}

inline void system_mixer_pause_channel(i32 channel) {
    Mix_HaltChannel(channel);
}

void system_mixer_music_fade_in(i32 loop, i32 ms) {
    Mix_FadeInMusic(current_track, loop, ms);
}

void system_mixer_music_volume(i32 volume) {
    // div 2 because LBA use 255 range and SDL_mixer use 128 range
    Mix_VolumeMusic(volume / 2);
}

void system_mixer_music_fade_out(i32 ms) {
    while (!Mix_FadeOutMusic(ms) && Mix_PlayingMusic()) {
        SDL_Delay(100);
    }
    Mix_HaltMusic();
    Mix_RewindMusic();
}

inline void system_mixer_load_music(u8 *music_ptr, i32 music_size) {
    SDL_IOStream *rw = SDL_IOFromMem(music_ptr, music_size);
    current_track = Mix_LoadMUS_IO(rw, TRUE);
}

i32 system_mixer_free_music() {
    if (current_track != NULL) {
        Mix_FreeMusic(current_track);
        current_track = NULL;
        return 1;
    }
    return 0;
}

i32 system_mixer_play_music(u8 *music_ptr, i32 music_size, i32 loop) {
    system_mixer_load_music(music_ptr, music_size);
    return Mix_PlayMusic(current_track, loop);
}

i32 system_mixer_play_music_mp3(c8 *music_file) {
    int error_code = 0;
    current_track = Mix_LoadMUS(music_file);
    if (current_track == NULL)
        printf("Mix_LoadMUS: %s\n", SDL_GetError());
    error_code = Mix_PlayMusic(current_track, -1);
    if (error_code == -1) {
        printf("Mix_PlayMusic: %s\n", SDL_GetError());
    }
    return error_code;
}

void system_mixer_stop_music_mp3() {
    if (current_track != NULL) {
        Mix_FreeMusic(current_track);
        current_track = NULL;
    }
}
