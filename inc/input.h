#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

_Bool keysprocessed[SDL_NUM_SCANCODES];
_Bool buttonsprocessed[5];
void input_init(void);
void input_poll(void);
int input_get_keystate(int keycode);
void input_get_mousemotion(int *x, int *y);
int input_get_buttonstate(int button);
int input_get_closestate(void);
void input_set_closestate();

#endif
