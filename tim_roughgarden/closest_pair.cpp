#include <iostream>
#include <math.h>
#include <algorithm>
#include <climits>

#define MAXN 200000

#define pair std::pair<point, point>

class point {
public:
	double x;
	double y;
};

bool comp_x(point& a, point& b) { return a.x < b.x; }
bool comp_y(point& a, point& b) { return a.y < b.y; }

double d(pair a) {
	return std::sqrt((a.first.x - a.second.x) * (a.first.x - a.second.x) + (a.first.y - a.second.y) * (a.first.y - a.second.y));
}

point Sy[MAXN];
pair closest_split_pair(point arr1[], point arr2[], double& best, int& size) {
	double min_x = arr1[size / 2 - 1].x - best, max_x = arr1[size / 2].x + best;
	int k = 0;
	while (arr1[k].x < min_x) k++;
	int size_Sy;
	for (size_Sy = k; size_Sy < size && arr1[size_Sy].x <= max_x; size_Sy++)
		Sy[size_Sy - k] = arr1[size_Sy];
	size_Sy -= k + 1;
	std::sort(Sy, Sy + size_Sy, comp_y);
	double g = best;
	point a;
	a.x = 0, a.y = 0;
	point l;
	l.x = INT_MAX, l.y = INT_MAX;
	pair b(a, l);
	for (int i = 0; i < size_Sy; i++)
		for (int j = 0; j < std::min(7, size_Sy - i); j++) {
			point m = Sy[i], n = Sy[i + j + 1];
			pair tmp(m, n);
			if (d(tmp) < g)
				b = tmp, g = d(tmp);
		}
	return b;
}

pair closest_pair(point arr1[], point arr2[], int size) {
	if (size <= 1) {
		point a;
		a.x = 0, a.y = 0;
		point b;
		b.x = INT_MAX, b.y = INT_MAX;
		pair k(a, b);
		return k;
	}
	pair left_half = closest_pair(arr1, arr2, size / 2);
	pair right_half = closest_pair(arr1 + size / 2, arr2 + size / 2, (size + 1) / 2);
	double best = std::min(d(left_half), d(right_half));
	pair greatest;
	if (d(left_half) < d(right_half))
		greatest = left_half;
	else
		greatest = right_half;
	pair split = closest_split_pair(arr1, arr2, best, size);
	if (d(split) < d(greatest))
		greatest = split;
	return greatest;
}

point sorted_by_x[MAXN];
point sorted_by_y[MAXN];
pair closest_pair(point arr[], int size) {
	for (int i = 0; i < size; i++)
		sorted_by_x[i].x = arr[i].x, sorted_by_x[i].y = arr[i].y;
	std::sort(sorted_by_x, sorted_by_x + size, comp_x);

	for (int i = 0; i < size; i++)
		sorted_by_y[i].x = arr[i].x, sorted_by_y[i].y = arr[i].y;
	std::sort(sorted_by_y, sorted_by_y + size, comp_y);

	pair ret = closest_pair(sorted_by_x, sorted_by_y, size);

	return ret;
}


point point_set[MAXN];

int main() {
	int size;
	std::cin >> size;
	for (int i = 0; i < size; i++)
		std::cin >> point_set[i].x >> point_set[i].y;

	pair best = closest_pair(point_set, size);

	printf("%.4f\n", d(best));

	return 0;
}