#include <stdio.h>
#include <stdlib.h>
#include <audio.h>

static size_t music_count = 0;
static FMOD_SOUND **music;

static size_t chunk_count = 0;
static FMOD_SOUND **chunk;

FMOD_SYSTEM *fmodsystem;
FMOD_CHANNELGROUP *music_channelgroup;
FMOD_CHANNELGROUP *chunk_channelgroup;

#define ASSERT_FMOD(C, M) \
if (C != FMOD_OK) { fprintf(stderr, "audio: %s\n", M); fflush(stderr); return; }

void audio_init(void)
{
	ASSERT_FMOD(FMOD_System_Create(&fmodsystem), "failed to create fmod system")
	ASSERT_FMOD(FMOD_System_Init(fmodsystem, 32, FMOD_INIT_NORMAL, NULL), "failed to init fmod system")
}

void audio_load_music(char **files, size_t count)
{
	music_count = count;
	music = calloc(count, sizeof(FMOD_SOUND *));

	FMOD_System_CreateChannelGroup(fmodsystem, "music_channelgroup", &music_channelgroup);

	for (size_t i = 0; i < count; i++) {
		if (FMOD_OK != FMOD_System_CreateSound(fmodsystem, files[i], FMOD_DEFAULT, NULL, &music[i]))
			fprintf(stderr, "Failed to load audio - %s\n", files[i]);
	}
}

void audio_load_chunk(char **files, size_t count)
{
	chunk_count = count;
	chunk = calloc(count, sizeof(FMOD_SOUND *));

	FMOD_System_CreateChannelGroup(fmodsystem, "chunk_channelgroup", &chunk_channelgroup);

	for (size_t i = 0; i < count; i++) {
		if (FMOD_OK != FMOD_System_CreateSound(fmodsystem, files[i], FMOD_DEFAULT, NULL, &chunk[i]))
			fprintf(stderr, "Failed to load audio - %s\n", files[i]);
	}
}

void audio_playmusic(size_t i)
{
	if (i > music_count)
		return;

	ASSERT_FMOD(FMOD_System_PlaySound(fmodsystem, music[i], music_channelgroup, 0, NULL), "failed to play music")
}

void audio_playchunk(size_t i)
{
	if (i > chunk_count)
		return;

	ASSERT_FMOD(FMOD_System_PlaySound(fmodsystem, chunk[i], chunk_channelgroup, 0, NULL), "failed to play chunk")
}

void audio_update(void)
{
	ASSERT_FMOD(FMOD_System_Update(fmodsystem), "failed to update fmod system")
}

void audio_kill(void)
{
	size_t i;

	for (i = 0; i < music_count; i++)
		FMOD_Sound_Release(music[i]);
	for (i = 0; i < chunk_count; i++)
		FMOD_Sound_Release(chunk[i]);

	FMOD_ChannelGroup_Release(chunk_channelgroup);
	FMOD_ChannelGroup_Release(music_channelgroup);

	FMOD_System_Close(fmodsystem);
	FMOD_System_Release(fmodsystem);
}
