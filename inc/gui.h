#ifndef GUI_H
#define GUI_H

#include <shader.h>
#include <sprite.h>
#include <input.h>
#include <aabb.h>
#include <text.h>
#include <texture.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GUI_CENTERED 0xFFFF

typedef char ** gui_str;

void gui_init(int width, int height, int fontscale);
char **gui_string(char *str, size_t *num);
void gui_free_string(char **guistr, size_t num);
void gui_dialog_box(char **text, size_t elements, float scale);

#endif
