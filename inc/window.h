#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

void window_init(char *title, int size_x, int size_y);
void window_resize(int size_x, int size_y);
void window_destroy(void);

void window_gl_makecurrent();
SDL_Window *get_window(void);

#endif
