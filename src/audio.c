#include <stdio.h>
#include <stdlib.h>
#include <audio.h>

static size_t music_count = 0;
static Mix_Music **music;

static size_t chunk_count = 0;
static Mix_Chunk **chunk;

void audio_init(void)
{
	if(Mix_OpenAudio(48000, AUDIO_F32SYS, 2, 2048)) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return;
	}

	if (Mix_AllocateChannels(2))
		fprintf(stderr, "%s\n", SDL_GetError());
}

void audio_load_music(char **files, size_t count)
{
	music_count = count;
	music = calloc(count, sizeof(Mix_Music *));

	for (size_t i = 0; i < count; i++) {
		music[i] = Mix_LoadMUS(files[i]);
		if (!music[i])
			fprintf(stderr, "Failed to load audio - %s\n", files[i]);
	}
}

void audio_load_chunk(char **files, size_t count)
{
	chunk_count = count;
	chunk = calloc(count, sizeof(Mix_Chunk *));

	for (size_t i = 0; i < count; i++) {
		chunk[i] = Mix_LoadWAV(files[i]);
		if (!chunk[i])
			fprintf(stderr, "Failed to load audio - %s\n", files[i]);
	}
}

void audio_playmusic(size_t i, int loops)
{
	if (i > music_count)
		return;

	Mix_PlayMusic(music[i], loops);
}

void audio_playchunk(size_t i, int loops)
{
	if (i > chunk_count)
		return;

	Mix_PlayChannel(-1, chunk[i], loops);
}

void audio_kill(void)
{
	size_t i;

	for (i = 0; i < music_count; i++)
		Mix_FreeMusic(music[i]);
	for (i = 0; i < chunk_count; i++)
		Mix_FreeChunk(chunk[i]);

	Mix_CloseAudio();
}
