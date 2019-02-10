#include <gui.h>

static GLuint shader, dialog_tex;
static int w, h;
static int fontscale;

#define CENTER_TEXT_X(pos, size, str, scale) ((pos[0]+(size[0]/2))-((strlen(str) * ((fontscale/2)*scale))/2))

void gui_init(int width, int height, int scale)
{
	fontscale = scale;
	w = width;
	h = height;
	shader = shader_binary_cache("shaders/cached/gui.glsp", "shaders/vdbg.glsl", "shaders/fdbg.glsl");
	dialog_tex = texture_create("textures/dialog.png");
}

char **gui_string(char *str, size_t *num)
{
	size_t numstr=0;
	char **strings;
	char *to_be_parsed;
	size_t i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '\n') {
			numstr++;
		}
	}

	strings = malloc(numstr * sizeof(char *));
	to_be_parsed = malloc(strlen(str));
	strcpy(to_be_parsed, str);

	for (i = 0; i < numstr; i++) {
		if (i == 0)
			strings[i] = strtok(to_be_parsed, "\n");
		else
			strings[i] = strtok(NULL, "\n");
	}
	
	if (num != NULL)
		*num = numstr;

	return strings;
}

void gui_free_string(char **guistr, size_t num)
{
	size_t i;
	for (i = 0; i < num; i++) {
		free(guistr[i]);
	}

	free(guistr);
}

void gui_dialog_box(char **text, size_t elements, float scale)
{
	vec3 white = {1.0f, 1.0f, 1.0f};
	vec2 dialog_size = {600, 200};
	vec2 dialog_pos = {(w/2)-dialog_size[0]/2, (h/4)-dialog_size[1]/2};

	sprite_draw(dialog_tex, shader, dialog_pos, dialog_size);

	size_t i;
	for (i = 0; i < elements; i++) {
		text_draw(text[i], CENTER_TEXT_X(dialog_pos, dialog_size, text[i], scale), (dialog_pos[1]+dialog_size[1])-(dialog_size[1]/8) - fontscale * i, scale, white);
	}
}
