#include "Geometry.h"

bool cmp(point_2D a, point_2D b) {
	if (a.x == b.x)
		return a.y < b.y;
	else return a.x < b.x;
}

point_2D* Monotone_Chain(point_2D pts[], int size) {
	point_2D* hull = new point_2D[2 * size];
	int k = 0;
	std::sort(pts, pts + size, cmp);
	for (int i = 0; i < size; i++) {
		while (k >= 2 && orientation(hull[k - 2], hull[k - 1], pts[i]) <= 0))
		k--;
		hull[k++] = pts[i];
	}

	int index = 1;
	point_2D last = hull[0];
	for (int i = 1; i < k - 1; i++)
		if (hull[i] != last)
			hull[index++] = last = hull[i];

	return hull;
}