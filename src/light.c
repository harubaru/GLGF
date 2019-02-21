#include <light.h>

static int width, height;
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
	
	for (int i = 0; i < 2; i++)
		ret.normal[i] = (size[i] / 2);

	return ret;
}

void light_init(int w, int h)
{
	width = w;
	height = h;
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

void light_draw_centered(light_t light)
{
	vec2 light_pos_offset = { (width/2) - light.normal[0], (height/2) - light.normal[1] };
	glUniform3f(glGetUniformLocation(shader, "color"), light.color[0], light.color[1], light.color[2]);
	sprite_draw(0, shader, light_pos_offset, light.size);
}

void light_scene_draw_offset(light_t light, vec2 offset)
{
	if (!offset)
		return;

	vec2 light_pos_offset = { (width/2) - light.normal[0], (height/2) - light.normal[1] };
	
	for (int i = 0; i < 2; i++)
		offset[i] = light_pos_offset[i] - light.position[i];
}

void light_unbind(void)
{
	shader_bind(0);
}
