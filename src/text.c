#include <stdio.h>
#include <text.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct glyph {
	GLuint tex;
	int size[2];
	int bearing[2];
	GLuint advance;
} glyph_t;

static glyph_t characters[128];

static GLuint vao;
static GLuint vbo;
static GLuint shader;

static mat4x4 projection;
static int fontsize;

void text_init(char *font, int size)
{
	fontsize = size;
	shader = shader_binary_cache("shaders/cached/text.glsp", "shaders/vt.glsl", "shaders/ft.glsl");
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		fprintf(stderr, "FreeType2 failed to initialize\n");
		return;
	}

	FT_Face face;
	if (FT_New_Face(ft, font, 0, &face)) {
		fprintf(stderr, "Failed to load font: %s\n", font);
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			fprintf(stderr, "Failed to load glyph: %u\n", c);
			continue;
		}

		unsigned int tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glyph_t character;
		character.tex = tex;
		character.size[0] = face->glyph->bitmap.width;
		character.size[1] = face->glyph->bitmap.rows;
		character.bearing[0] = face->glyph->bitmap_left;
		character.bearing[1] = face->glyph->bitmap_top;
		character.advance = face->glyph->advance.x;

		characters[c] = character;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void text_projection(int w, int h)
{
	mat4x4_identity(projection);
	mat4x4_ortho(projection, 0.0f, (float)w, 0.0f, (float)h, -1, 1);
}

void text_draw(char *text, float x, float y, float scale, vec3 color)
{
	shader_bind(shader);

	glUniformMatrix4fv(glGetUniformLocation(shader, "Projection"), 1, GL_FALSE, *projection);
	glUniform3f(glGetUniformLocation(shader, "color"), color[0], color[1], color[2]);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	size_t len = strlen(text);
	float xpos;
	float ypos;

	for (size_t i = 0; i < len; i++) {
		unsigned char letter = text[i];
		glyph_t ch = characters[letter];

		xpos = x + ch.bearing[0] * scale;
		ypos = y - (ch.size[1] - ch.bearing[1]) * scale;

		float w = ch.size[0] * scale;
		float h = ch.size[1] * scale;

		float vertices[6][4] = {
			{xpos, ypos+h, 0.0, 0.0},
			{xpos, ypos,   0.0, 1.0},
			{xpos+w, ypos, 1.0, 1.0},
			
			{xpos, ypos+h, 0.0, 0.0},
			{xpos+w, ypos, 1.0, 1.0},
			{xpos+w,ypos+h,1.0, 0.0}
		};

		glBindTexture(GL_TEXTURE_2D, ch.tex);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * (6*4), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader_bind(0);
}
