#include <aabb.h>

aabb_t aabb_gen_quad(vec2 bp, vec2 bs)
{
	aabb_t aabb;

	for (int i = 0; i < 2; i++) {
		aabb.min[i] = bp[i];
		aabb.max[i] = bp[i] + bs[i];
	}

	return aabb;
}

_Bool aabb_point_intersect(vec2 point, aabb_t a)
{
	return (point[0] >= a.min[0] && point[0] <= a.max[0]) && (point[1] >= a.min[1] && point[1] <= a.max[1]);
}

_Bool aabb_quad_intersect(aabb_t a, aabb_t b)
{
	return (a.min[0] <= b.max[0] && a.max[0] >= b.min[0]) && (a.min[1] <= b.max[1] && a.max[1] >= b.min[1]);
}

float aabb_ray_distance(vec2 rp, vec2 rd, aabb_t a)
{
	vec4 m;

	m[0] = -INFINITY;
	m[1] = INFINITY;

	for (int i = 0; i < 2; i++) {
		m[2] = (a.min[i] - rp[i]) / rd[i];
		m[3] = (a.max[i] - rp[i]) / rd[i];

		if (m[2] > m[3]) {
			float tmp = m[2];
			m[2] = m[3];
			m[3] = tmp;
		}

		if ((m[3] < m[0]) || (m[2] > m[1]))
			return INFINITY;

		if (m[2] > m[0]) m[0] = m[2];
		if (m[3] < m[1]) m[1] = m[3];
	}

	return (m[0] > m[1]) ? INFINITY : m[0];
}

_Bool aabb_ray_intersect(float *distance, vec2 rp, vec2 rd, aabb_t a)
{
	float d = aabb_ray_distance(rp, rd, a);

	if (d == INFINITY) {
		return 0;
	} else {
		if (distance)
			*distance = d;
	}

	return 1;
}
