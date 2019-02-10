#ifndef TEXTURE_H
#define TEXTURE_H

#include <gl3w.h>
#include <stb_image.h>

GLuint texture_create(const char *filepath);
void texture_bind(GLuint id, GLuint unit);
void texture_destroy(GLuint id);

#endif
