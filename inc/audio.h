#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

void audio_init(char **audiofiles);
void audio_play(int i, int loops);
void audio_kill(void);

#endif
