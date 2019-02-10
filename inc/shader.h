#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <gl3w.h>

// GLSP = GL Shader Program
#define GL_SHADER_IDENT (('P' << 24) + ('S' << 16) + ('L' << 8) + 'G') 

typedef struct glshader_header {
	GLuint ident;
	GLsizei length;
	GLenum binaryformat;
} glshader_header_t;

GLuint shader_load(char *vertpath, char *fragpath);
int shader_binary_cache(char *binpath, char *vertpath, char *fragpath);
void shader_binary_save(GLuint program, char *binpath);
GLuint shader_binary_load(char *binpath);
void shader_bind(GLuint shader);
void shader_destroy(GLuint shader);

#endif
