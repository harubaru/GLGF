#include <postprocessing.h>

static int width = 0, height = 0;
static GLuint fbo;
static GLuint tex[2];
static GLuint shader = 0;

static GLuint gblur_fbo[2];
static GLuint gblur_tex[2];
static GLuint gblur_shader;

static void gblur_init(int w, int h)
{
	glGenFramebuffers(2, gblur_fbo);
	glGenTextures(2, gblur_tex);

	for (int i = 0; i < 2; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, gblur_fbo[i]);
		glBindTexture(GL_TEXTURE_2D, gblur_tex[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gblur_tex[i], 0);
	}
}

void postprocessing_init(int w, int h)
{
	width = w;
	height = h;

	glGenFramebuffers(1, &fbo);
	glGenTextures(2, tex);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	for (int i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, tex[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex[i], 0);
	}

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	shader = shader_binary_cache("./shaders/cached/fb.glsp", "./shaders/vfb.glsl", "./shaders/ffb.glsl");
	gblur_shader = shader_binary_cache("./shaders/cached/gblur.glsp", "./shaders/vfb.glsl", "./shaders/fgblur.glsl");

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	gblur_init(w, h);
}

void postprocessing_kill(void)
{
	glDeleteTextures(2, tex);
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
	int h = 1, f = 1;

	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT);
	shader_bind(gblur_shader);

	for (int i = 0; i < 10; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, gblur_fbo[h]);
		glUniform1i(glGetUniformLocation(gblur_shader, "horizontal"), h);
		sprite_draw((f == 1) ? tex[1] : gblur_tex[!h], gblur_shader, pos, size);

		h = !h;
		if (f) f = 0;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shader_bind(shader);
	glUniform1i(glGetUniformLocation(shader, "image"), 0);
	glUniform1i(glGetUniformLocation(shader, "image2"), 1);
	sprite_draw_multitextured(tex[0], gblur_tex[!h], shader, pos, size);
	glEnable(GL_BLEND);
}
