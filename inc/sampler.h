#ifndef SAMPLER_H
#define SAMPLER_H

#include <gl3w.h>

typedef struct sampler_createinfo {
	GLint wrap_s;
	GLint wrap_t;
	GLint min_filter;
	GLint mag_filter;
	GLfloat min_lod;
	GLfloat max_lod;
	GLfloat lod_bias;
} sampler_createinfo_t;

sampler_createinfo_t sampler_createinfo_default();
GLuint sampler_init(sampler_createinfo_t createinfo);
void sampler_bind(GLuint sampler, GLuint texunit);
void sampler_destroy(GLuint sampler);

#endif
