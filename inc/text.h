#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <string.h>
#include <linmath.h>
#include <shader.h>

void text_init(char *font, int size);
void text_projection(int w, int h);
void text_draw(char *text, float x, float y, float scale, vec3 color);

#endif
