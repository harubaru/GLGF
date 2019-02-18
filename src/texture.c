#include <texture.h>

GLuint texture_create(const char *filepath)
{
	stbi_set_flip_vertically_on_load(1);

	GLuint id = 0;
	GLenum iformat = 0, format = 0;
	int width, height, components;
	unsigned char *data = stbi_load(filepath, &width, &height, &components, 0);

	if (!data)
		return 0;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	if (components == 3) {
		iformat = GL_SRGB;
		format = GL_RGB;
	} else if (components == 4) {
		iformat = GL_SRGB_ALPHA;
		format = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}

void texture_bind(GLuint id, GLuint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void texture_destroy(GLuint id)
{
	glDeleteTextures(1, &id);
}
