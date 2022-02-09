#include "Geometry.h"

bool cmp_polar(point_2D& O, point_2D& a, point_2D& b) {
	double m1 = sqrt(a.x * a.x + a.y * a.y);
	double m2 = sqrt(b.x * b.x + b.y * b.y);
	double v1 = (a.x - O.x) * (b.y - O.y) - (a.y - O.y) * (b.x - O.x);
	return v1 > 0 || (v1 == 0 && m1 < m2);
}

int LTL(point_2D P[], int n) {
	int ltl = 0;
	for (int i = 1; i < n; i++)
		if (P[i].y < P[ltl].y || (P[i].y == P[ltl].y && P[i].x < P[ltl].x))
			ltl = i;
	return ltl;
}

std::stack<point_2D> Jarvis_March(point_2D point_set[], int size) {
	std::stack<point_2D> stack;
	int ltl = LTL(point_set, size);
	int k = ltl;
	do {
		stack.push(point_set[k]);
		int s = -1;
		for(int t = 0; t < size; t++)
			if(t != k && (s == -1 || cmp_polar(point_set[k], point_set[s], point_set[t])))
				s = t;
		k = s;
	} while (ltl != k);
	return stack;
}