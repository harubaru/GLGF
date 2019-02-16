#ifndef SPRITE_H
#define SPRITE_H

#include <linmath.h>
#include <gl3w.h>

#include <texture.h>
#include <shader.h>

void sprite_init();
void sprite_destroy();
void sprite_projection(int w, int h);
void sprite_draw(GLuint texture, GLuint shader, vec2 position, vec2 size);
void sprite_draw_multitextured(GLuint texture1, GLuint texture2, GLuint shader, vec2 position, vec2 size);

#endif
