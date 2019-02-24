#ifndef AABB_H
#define AABB_H

#include <linmath.h>

typedef struct aabb {
	vec2 min;
	vec2 max;
} aabb_t;

aabb_t aabb_gen_quad(vec2 bp, vec2 bs);

_Bool aabb_point_intersect(vec2 point, vec2 bp, vec2 bs);
_Bool aabb_quad_intersect(vec2 bp1, vec2 bs1, vec2 bp2, vec2 bs2);
float aabb_ray_distance(vec2 rp, vec2 rd, vec2 bp, vec2 bs);
_Bool aabb_ray_intersect(float *distance, vec2 rp, vec2 rd, vec2 bp, vec2 bs);

#endif
