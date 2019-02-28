#include <physics.h>

#define GRAVITY 9.8

typedef struct node {
	struct node *next;
	int fetched;
	phys_body_t *body;
} node_t;

node_t *bodies = NULL;
static unsigned int bodycount = 0;

void physics_body_add(phys_body_t *body)
{
	bodycount++;

	if (!bodies) {
		bodies = calloc(1, sizeof(node_t));
		bodies->next = NULL;
		bodies->body = body;
		bodies->fetched = 1;

		return;
	}

	node_t *newbody = calloc(1, sizeof(node_t));
	newbody->next = bodies;
	newbody->body = body;
	bodies = newbody;
	bodies->fetched = 1;
}

void physics_body_remove(phys_body_t *body)
{
	if (!bodies)
		return;
	
	node_t *curr = bodies;
	node_t *prev = NULL;

	while (curr != NULL) {
		if (curr->body == body) {
			if (prev) {
				prev->next = curr->next;
			}

			bodycount--;
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->next;
	}
}

void physics_body_fetch(phys_body_t *body)
{
	if (!bodies)
		return;
	
	node_t *curr = bodies;

	while (curr != NULL) {
		if (curr->fetched == 1) {
			*body = *curr->body;
			curr->fetched = 0;
			break;
		}

		curr = curr->next;
	}
}

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

void physics_body_compute(phys_body_t *a, phys_body_t *b, float deltatime)
{
	vec2 force;

	force[0] = 0;
	force[1] -= GRAVITY;

	if (aabb_quad_intersect(a->aabb, b->aabb))
		force[1] = 0;

	for (int i = 0; i < 2; i++)
		a->velocity[i] += force[i] * (deltatime);

	for (int i = 0; i < 2; i++)
		a->position[i] += a->velocity[i];
}
