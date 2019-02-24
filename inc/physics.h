#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>

#include <aabb.h>
#include <linmath.h>

typedef struct phys_body {
	aabb_t aabb;
	vec2 position;
	vec2 size;
	vec2 velocity;
} phys_body_t;

phys_body_t *physics_body_init(vec2 pos, vec2 size);
void physics_body_step(phys_body_t *body, float deltatime);

#endif
