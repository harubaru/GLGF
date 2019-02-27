#include <stdio.h>
#include <window.h>
#include <graphics.h>

void graphics_init(void)
{
	switch(gl3wInit()) {
	case GL3W_OK:
		break;
	case GL3W_ERROR_INIT:
		fprintf(stderr, "Failed to detect OpenGL version!\n");
		abort();
		break;
	case GL3W_ERROR_LIBRARY_OPEN:
		fprintf(stderr, "Failed to detect OpenGL library!\n");
		abort();
		break;
	case GL3W_ERROR_OPENGL_VERSION:
		printf("%s\n", glGetString(GL_VENDOR));
		fprintf(stderr, "OpenGL Version 3.3 or higher is required to run this program!\n");
		abort();
		break;
	default:
		fprintf(stderr, "Failed to load OpenGL!\n");
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
