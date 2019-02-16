#include <light.h>

static GLuint shader;

light_t light_create(vec2 position, vec2 size, vec3 color)
{
	light_t ret;
	int i;

	for (i = 0; i < 2; i++) {
		ret.position[i] = position[i];
		ret.size[i] = size[i];
	}

	for (int i = 0; i < 3; i++)
		ret.color[i] = color[i];

	return ret;
}

void light_init(void)
{
	shader = shader_binary_cache("./shaders/cached/light.glsp", "./shaders/vdbg.glsl", "./shaders/flight.glsl");
}

void light_bind(void)
{
	shader_bind(shader);
}

void light_draw(light_t light)
{
	glUniform3f(glGetUniformLocation(shader, "color"), light.color[0], light.color[1], light.color[2]);
	sprite_draw(0, shader, light.position, light.size);
}

void light_unbind(void)
{
	shader_bind(0);
}
