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

_Bool aabb_point_intersect(vec2 point, vec2 bp, vec2 bs)
{
	vec2 min, max;

	for (int i = 0; i < 2; i++) {
		min[i] = bp[i];
		max[i] = bp[i] + bs[i];
	}

	return (point[0] >= min[0] && point[0] <= max[0]) && (point[1] >= min[1] && point[1] <= max[1]);
}

_Bool aabb_quad_intersect(vec2 bp1, vec2 bs1, vec2 bp2, vec2 bs2)
{
	vec2 min1, max1, min2, max2;

	for (int i = 0; i < 2; i++) {
		min1[i] = bp1[i];
		max1[i] = bp1[i] + bs1[i];
	}
	for (int i = 0; i < 2; i++) {
		min2[i] = bp2[i];
		max2[i] = bp2[i] + bs2[i];
	}

	return (min1[0] <= max2[0] && max1[0] >= min2[0]) && (min1[1] <= max2[1] && max1[1] >= min2[1]);
}

float aabb_ray_distance(vec2 rp, vec2 rd, vec2 bp, vec2 bs)
{
	vec2 min, max;
	vec4 m;

	for(int i = 0; i < 2; i++) {
		min[i] = bp[i];
		max[i] = bp[i] + bs[i];
	}

	m[0] = -INFINITY;
	m[1] = INFINITY;

	for (int i = 0; i < 2; i++) {
		m[2] = (min[i] - rp[i]) / rd[i];
		m[3] = (max[i] - rp[i]) / rd[i];

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

_Bool aabb_ray_intersect(float *distance, vec2 rp, vec2 rd, vec2 bp, vec2 bs)
{
	vec2 min, max;

	for(int i = 0; i < 2; i++) {
		min[i] = bp[i];
		max[i] = bp[i] + bs[i];
	}

	float d = aabb_ray_distance(rp, rd, bp, bs);

	if (d == INFINITY) {
		return 0;
	} else {
		if (distance)
			*distance = d;
	}

	return 1;
}
