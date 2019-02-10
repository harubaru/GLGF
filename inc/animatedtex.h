#ifndef ANIMATEDTEX_H
#define ANIMATEDTEX_H

#include <stdlib.h>
#include <texture.h>

typedef struct animatedtex {
	GLuint *id;
	GLuint cur_id;
	float next;
	float freq;
	size_t amount;
} animatedtex_t;

animatedtex_t *animatedtex_init(char **filenames, size_t amount, float freq);
void animatedtex_update(animatedtex_t *tex, float deltatime);
void animatedtex_destroy(animatedtex_t *tex);

#endif
