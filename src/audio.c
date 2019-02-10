#include <stdio.h>
#include <audio.h>

Mix_Music *sample[2];

void audio_init(char **audiofiles)
{
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512)) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return;
	}
	if (Mix_AllocateChannels(2)) {
		fprintf(stderr, "%s\n", SDL_GetError());
	}

	for (int i = 0; i < 2; i++) {
		sample[i] = Mix_LoadOGG(audiofiles[i]);
		if (!sample[i])
			fprintf(stderr, "failed to load %s\n", audiofiles[i]);
	}
}

void audio_play(int i, int loops)
{
	Mix_PlayMusic(sample[i], loops);
}

void audio_kill(void)
{
	for (int i = 0; i < 2; i++)
		Mix_FreeMusic(sample[i]);

	Mix_CloseAudio();
}
