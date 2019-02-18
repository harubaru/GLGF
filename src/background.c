#include <background.h>

static GLuint bg_tex;
static vec2 pos = {.0, .0};

void background_load(char *filename)
{
	bg_tex = texture_create(filename);
}

void background_draw(GLuint shader, vec2 offset, float parallaxfactor, vec2 size)
{	
	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "parallaxbg"), 1);
	glUniform2f(glGetUniformLocation(shader, "parallaxoffset"), offset[0] * parallaxfactor, offset[1] * parallaxfactor);
	glUseProgram(0);

	sprite_draw(bg_tex, shader, pos, size);

	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "parallaxbg"), 0);
	glUseProgram(0);
}

void background_destroy(void)
{
	texture_destroy(bg_tex);
}
