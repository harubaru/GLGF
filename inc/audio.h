#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

void audio_init(void);
void audio_load_music(char **files, size_t count);
void audio_load_chunk(char **files, size_t count);
void audio_playmusic(size_t i, int loops);
void audio_playchunk(size_t i, int loops);
void audio_kill(void);

#endif
