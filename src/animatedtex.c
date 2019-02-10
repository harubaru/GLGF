#include <animatedtex.h>

/*
typedef struct animatedtex {
	GLuint *id;	// frames
	GLuint cur_id;	// current frame to render
	float next;	// time to next frame
	float freq;	// frequency of frame switching
	size_t amount;	// amount of frames
} animatedtex_t;
*/

animatedtex_t *animatedtex_init(char **filenames, size_t amount, float freq)
{
	animatedtex_t *tex = malloc(sizeof(animatedtex_t));
	if (!tex)
		return NULL;
	
	tex->id = calloc(1, sizeof(GLuint) * amount);
	if (!tex->id) {
		free(tex);
		return NULL;
	}

	size_t i;
	for (i = 0; i < amount; i++)
		tex->id[i] = texture_create(filenames[i]);

	tex->amount = amount;
	tex->freq = freq;
	tex->cur_id = 0;

	return tex;
}

void animatedtex_update(animatedtex_t *tex, float deltatime)
{
	tex->next -= deltatime;
	if (tex->next <= 0.0) {
		tex->next = tex->freq;
		tex->cur_id++;
		if (tex->cur_id >= tex->amount)
			tex->cur_id = 0; 
	}
}

void animatedtex_destroy(animatedtex_t *tex)
{
	if (!tex)
		return;

	size_t i;
	for (i = 0; i < tex->amount; i++)
		texture_destroy(tex->id[i]);

	free(tex);
}
