#include "Geometry.h"

bool cmp_print(point_2D& a, point_2D& b) {
	if (a.y == b.y)
		return a.x < b.x;
	return a.y < b.y;
}

point_2D pmin;

bool cmp_polar(point_2D& a, point_2D& b) {
	double m1 = sqrt(a.x * a.x + a.y * a.y);
	double m2 = sqrt(b.x * b.x + b.y * b.y);
	double v1 = (a.x - pmin.x) * (b.y - pmin.y) - (a.y - pmin.y) * (b.x - pmin.x);
	return v1 > 0 || (v1 == 0 && m1 < m2);
}

std::stack<point_2D> Graham_Scan(point_2D point_set[], int size) {
	std::stack<point_2D> hull;
	std::sort(point_set, point_set + size, cmp_print);
	pmin = point_set[0];
	std::sort(point_set, point_set + size, cmp_polar);
	int k1;
	for (k1 = 1; k1 < size; k1++)
		if (point_set[0] == point_set[k1])
			break;
	if (k1 == size)
		return hull;
	hull.push(point_set[0]);
	int k2;
	for (k2 = k1 + 1; k2 < size; k2++)
		if (collinear(point_set[0], point_set[k1], point_set[k2]) != 0)
			break;
	hull.push(point_set[k2 - 1]);
	for (int i = k2; i < size; i++) {
		point_2D top = hull.top();
		hull.pop();
		while (collinear(hull.top(), top, point_set[i]) <= 0)
			top = hull.top(), hull.pop();
		hull.push(top);
		hull.push(point_set[i]);
	}
	return hull;
}