#include <threads.h>
#include <window.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window = NULL;
static SDL_GLContext glcontext;
static SDL_GLContext glinitcontext;

void window_init(char *title, int size_x, int size_y)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		size_x,
		size_y,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	glcontext = SDL_GL_CreateContext(window);
	glinitcontext = SDL_GL_CreateContext(window);

	if (!window) {
		fprintf(stderr, "Unable to create window!\n Error:\n%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void window_resize(int size_x, int size_y)
{
	(void)size_x;
	(void)size_y;
}

void window_gl_makecurrent()
{
	SDL_GL_MakeCurrent(window, glcontext);
}

void window_destroy(void)
{
	if (window)
		SDL_DestroyWindow(window);

	SDL_GL_DeleteContext(glcontext);
	SDL_GL_DeleteContext(glinitcontext);
}

SDL_Window *get_window(void)
{
	return window;
}
