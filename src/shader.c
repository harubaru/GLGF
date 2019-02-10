#include <shader.h>

static char *read_file(char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	long size;
	char *source;

	if (!fp) {
		fprintf(stderr, "file not found - %s\n", filepath);
		return NULL;
	}

	/* get size of file */
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	/* read file into string */
	source = calloc(1, size + 1);
	fread(source, 1, size, fp);
	source[size] = 0;
	fclose(fp);

	return source;
}

static GLuint compile_shader(const char *source, GLuint type)
{
	int len = 0;
	GLuint s = glCreateShader(type);

	if (!glIsShader(s)) {
		fprintf(stderr, "wrong shader type\n");
		return 0;
	}

	glShaderSource(s, 1, &source, NULL);
	glCompileShader(s);

	glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);

	if (len > 0) {
		GLchar *log = malloc(len);
		glGetShaderInfoLog(s, len, NULL, log);
		fprintf(stderr, "%s", log);
		free(log);
	}

	return s;
}

static GLuint link_shaders(GLuint s1, GLuint s2)
{
	int len = 0;
	GLuint s = glCreateProgram();
	glAttachShader(s, s1);
	glAttachShader(s, s2);

	glLinkProgram(s);

	glGetProgramiv(s, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		GLchar *log = malloc(len);
		glGetProgramInfoLog(s, len, NULL, log);
		fprintf(stderr, "%s", log);
		free(log);
	}
	
	return s;
}

GLuint shader_load(char *vertpath, char *fragpath)
{
	GLuint vshader, fshader, shader;
	char *vsrc, *fsrc;

	vsrc = read_file(vertpath);
	fsrc = read_file(fragpath);

	vshader = compile_shader(vsrc, GL_VERTEX_SHADER);
	fshader = compile_shader(fsrc, GL_FRAGMENT_SHADER);
	
	shader = link_shaders(vshader, fshader);

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	free(vsrc);
	free(fsrc);

	return shader;
}

static int shader_binary_exists(char *binpath)
{
	FILE *fp = NULL;
	if ((fp = fopen(binpath, "r")) != NULL) {
		fclose(fp);
		return 1;
	}

	return 0;
}

int shader_binary_cache(char *binpath, char *vertpath, char *fragpath)
{
	if (shader_binary_exists(binpath)) {
		return shader_binary_load(binpath);
	}

	GLuint sp = shader_load(vertpath, fragpath);
	shader_binary_save(sp, binpath);

	return sp;
}

void shader_binary_save(GLuint program, char *binpath)
{
	FILE *fp = fopen(binpath, "wb");
	GLint size = 0;
	GLsizei length = 0;
	GLenum binaryformat = 0;
	void *binary = NULL;

	glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &size);
	binary = calloc(1, size);

	glGetProgramBinary(program, size, &length, &binaryformat, binary);

	glshader_header_t header;

	header.ident = GL_SHADER_IDENT;
	header.length = length;
	header.binaryformat = binaryformat;

	if (fp == NULL) {
		fprintf(stderr, "Unable to cache shader - %s\n", binpath);
		return;
	}

	fwrite(&header, sizeof(glshader_header_t), 1, fp);
	fwrite(binary, length, 1, fp);

	fclose(fp);
}

GLuint shader_binary_load(char *binpath)
{
	GLuint s = glCreateProgram();
	FILE *fp = fopen(binpath, "rb");
	void *binary = NULL;

	glshader_header_t header;
	fread(&header, sizeof(glshader_header_t), 1, fp);

	if (header.ident != GL_SHADER_IDENT) {
		fprintf(stderr, "Invalid shader program! - %s\n", binpath);
		fclose(fp);
		return 0;
	}

	binary = calloc(1, header.length);

	fread(binary, header.length, 1, fp);

	glProgramBinary(s, header.binaryformat, binary, header.length);

	free(binary);
	fclose(fp);
	return s;
}

void shader_bind(GLuint shader)
{
	glUseProgram(shader);
}

void shader_destroy(GLuint shader)
{
	glDeleteProgram(shader);
}
