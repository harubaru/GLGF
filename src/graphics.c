#include <stdio.h>
#include <window.h>
#include <graphics.h>

void graphics_init(void)
{
	int ret = gl3wInit();

	switch(ret) {
	case GL3W_OK:
		break;
	default:
		break;
	}

	glEnable(GL_BLEND);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

void graphics_clear(void)
{
	int w, h;
	SDL_GL_SwapWindow(get_window());
	SDL_GL_SetSwapInterval(1);
	SDL_GetWindowSize(get_window(), &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
