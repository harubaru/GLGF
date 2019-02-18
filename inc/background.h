#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <linmath.h>
#include <gl3w.h>
#include <texture.h>
#include <sprite.h>

void background_load(char *filename);
void background_draw(GLuint shader, vec2 offset, float parallaxfactor, vec2 size);
void background_destroy(void);

#endif