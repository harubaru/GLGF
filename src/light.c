#include <light.h>

static int width, height;
static GLuint shader;

typedef struct node {
	struct node *next;
	light_t *light;
	_Bool needsdrawn;
} node_t;

static node_t *lights = NULL; // head
static size_t lightcount = 0;

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

void light_add(light_t *light)
{
	lightcount++;

	if (!lights) {
		lights = calloc(1, sizeof(node_t));
		lights->next = NULL;
		lights->light = light;
		lights->needsdrawn = 1;

		return;
	}
	
	node_t *newlight = calloc(1, sizeof(node_t));
	newlight->next = lights;
	newlight->light = light;
	lights = newlight;
	lights->needsdrawn = 1;
}

void light_remove(light_t *light)
{
	if (!lights)
		return;
	
	node_t *curr = lights;
	node_t *prev = NULL;

	while (curr != NULL) {
		if (curr->light == light) {
			if (prev) {
				prev->next = curr->next;
			}
			lightcount--;
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->next;
	}
}

void light_fetch(light_t *light)
{
	if (!lights)
		return;
	
	node_t *curr = lights;

	while (curr != NULL) {
		if (curr->needsdrawn == 1) {
			*light = *curr->light;
			curr->needsdrawn = 0;
			break;
		}

		curr = curr->next;	
	}
}

void light_reset_queue()
{
	if (!lights)
		return;
	
	node_t *curr = lights;

	while (curr != NULL) {
		if (curr->needsdrawn == 0) {
			curr->needsdrawn = 1;
		}

		curr = curr->next;
	}
}

size_t light_get_count()
{
	return lightcount;
}

void light_bind(void)
{
	shader_bind(shader);
}

void light_draw(light_t light, vec2 pwo)
{
	glUniform3f(glGetUniformLocation(shader, "color"), light.color[0], light.color[1], light.color[2]);
	vec2 tilepos = { light.position[0] + pwo[0], light.position[1] + pwo[1] };
	sprite_draw(0, shader, tilepos, light.size);
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
