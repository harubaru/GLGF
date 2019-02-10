#include <aabb.h>

_Bool aabb_point_intersect(vec2 point, vec2 bp, vec2 bs)
{
	float xmin = bp[0];
	float xmax = bp[0] + bs[0];
	float ymin = bp[1];
	float ymax = bp[1] + bs[1];

	return (point[0] >= xmin && point[0] <= xmax) && (point[1] >= ymin && point[1] <= ymax);
}

_Bool aabb_quad_intersect(vec2 bp1, vec2 bs1, vec2 bp2, vec2 bs2)
{
	float xmin1 = bp1[0];
	float xmax1 = bp1[0] + bs1[0];
	float ymin1 = bp1[1];
	float ymax1 = bp1[1] + bs1[1];

	float xmin2 = bp2[0];
	float xmax2 = bp2[0] + bs2[0];
	float ymin2 = bp2[1];
	float ymax2 = bp2[1] + bs2[1];


	return (xmin1 <= xmax2 && xmax1 >= xmin2) && (ymin1 <= ymax2 && ymax1 >= ymin2);
}
