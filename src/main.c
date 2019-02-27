#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define W 640
#define H 480

#include <glgf.h>

int main()
{
	window_init("test", 640, 480);
	window_gl_makecurrent();
	input_init();
	graphics_init();
	sprite_init();

	GLuint spriteshader = shader_load("v.glsl", "f.glsl");
	GLuint texture = texture_create("texture.png");

	while(!input_get_closestate()) {
		input_poll();
		sprite_projection(W, H);
		vec2 pos = {0, 0};
		vec2 size = {W, H};
		sprite_draw(texture, spriteshader, pos, size);
		graphics_clear();
	}
}