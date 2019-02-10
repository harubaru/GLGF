#include <threads.h>
#include <input.h>

static _Bool keys[SDL_NUM_SCANCODES];
static _Bool buttons[5];
static int mouse[2];
static int close;

void input_init(void)
{
	int i;
	for (i = 0; i < SDL_NUM_SCANCODES; i++)
		keys[i] = 0;
	for (i = 0; i < 5; i++)
		buttons[i] = 0;

	close = 0;
}

void input_poll(void)
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_KEYDOWN:
			keys[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.scancode] = 0;
			keysprocessed[event.key.keysym.scancode] = 0;
			break;
		case SDL_MOUSEMOTION:
			mouse[0] = event.motion.x;
			mouse[1] = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			buttons[event.button.button-1] = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			buttons[event.button.button-1] = 0;
			buttonsprocessed[event.button.button-1] = 0;
			break;
		case SDL_QUIT:
			close = 1;
			break;
		default:
			break;
		}
	}
}

int input_get_keystate(int keycode)
{
	int key = 0;
	if (keycode < SDL_NUM_SCANCODES)
		key = keys[keycode];

	return key;
}

void input_get_mousemotion(int *x, int *y)
{
	*x = mouse[0];
	*y = mouse[1];
}

int input_get_buttonstate(int button)
{
	return buttons[button-1];
}

int input_get_closestate(void)
{
	return close;
}

void input_set_closestate()
{
	close = 1;
}
