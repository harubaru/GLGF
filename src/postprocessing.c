#include <postprocessing.h>

static int width = 0, height = 0;
static GLuint fbo = 0;
static GLuint tex = 0;
static GLuint shader = 0;

void postprocessing_init(int w, int h)
{
	width = w;
	height = h;

	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &tex);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

	shader = shader_binary_cache("./shaders/cached/fb.glsp", "./shaders/vfb.glsl", "./shaders/ffb.glsl");

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void postprocessing_kill(void)
{
	glDeleteTextures(1, &tex);
	glDeleteFramebuffers(1, &fbo);
}

void postprocessing_capture(int enable)
{
	if (enable) {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_COLOR_BUFFER_BIT);
	} else {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void postprocessing_draw(void)
{
	vec2 pos = {0, 0};
	vec2 size = {width, height};
	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT);
	sprite_draw(tex, shader, pos, size);
	glEnable(GL_BLEND);
}
