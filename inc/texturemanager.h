#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <gl3w.h>
#include <texture.h>

void texturemanager_init(char *resource_path);
GLuint texturemanager_getid(GLuint id);
void texturemanager_destroy();

#endif
