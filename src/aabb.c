#include <aabb.h>

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
