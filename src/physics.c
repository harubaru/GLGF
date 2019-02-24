#include <physics.h>

#define GRAVITY 9.8

phys_body_t *physics_body_init(vec2 pos, vec2 size)
{
	phys_body_t *body = calloc(1, sizeof(phys_body_t));

	body->aabb = aabb_gen_quad(pos, size);

	for (int i = 0; i < 2; i++) {
		body->position[i] = pos[i];
		body->size[i] = size[i];
		body->velocity[i] = 0.0;
	}

	return body;
}

void physics_body_step(phys_body_t *body, float deltatime)
{
	vec2 force;

	force[0] = 0;
	force[1] = 9.8;

	for (int i = 0; i < 2; i++)
		body->velocity[i] += force[i] * (deltatime);

	for (int i = 0; i < 2; i++)
		body->position[i] += body->velocity[i];
}
