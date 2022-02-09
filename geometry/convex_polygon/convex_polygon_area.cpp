#include "Geometry.h"

double area(point_2D pts[], int size) {
	double a = 0;
	for (int i = 2; i < size; i++) {
		triangle t(pts[0], pts[i - 1], pts[i]);
		a += t.area();
	}
	return a;
}