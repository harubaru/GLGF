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

float aabb_ray_distance(vec2 rp, vec2 rd, vec2 bp, vec2 bs)
{
	vec2 min, max;

	for(int i = 0; i < 2; i++) {
		min[i] = bp[i];
		max[i] = bp[i] + bs[i];
	}

	float lo = -INFINITY;
	float hi = INFINITY;

	for (int i = 0; i < 2; i++) {
		float dimlo = (min[i] - rp[i]) / rd[i];
		float dimhi = (max[i] - rp[i]) / rd[i];

		if (dimlo > dimhi) {
			float tmp = dimlo;
			dimlo = dimhi;
			dimhi = tmp;
		}

		if ((dimhi < lo) || (dimlo > hi))
			return INFINITY;

		if (dimlo > lo) lo = dimlo;
		if (dimhi < hi) hi = dimhi;
	}

	return (lo > hi) ? INFINITY : lo;
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
