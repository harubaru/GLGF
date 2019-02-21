#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <gl3w.h>
#include <shader.h>
#include <sprite.h>

void postprocessing_init(int w, int h);
void postprocessing_kill(void);
void postprocessing_capture(int enable);
GLuint postprocessing_get_lightoccluders(void);
void postprocessing_draw(void);

#endif
