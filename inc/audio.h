#ifndef AUDIO_H
#define AUDIO_H

#include <fmod/fmod.h>

void audio_init(void);
void audio_load_music(char **files, size_t count);
void audio_load_chunk(char **files, size_t count);
void audio_playmusic(size_t i);
void audio_playchunk(size_t i);
void audio_update(void);
void audio_kill(void);

#endif
