#include <iostream>
#include <math.h>
#include <algorithm>
#include <climits>

#define MAXN 400005

#define pair std::pair<point, point>

#define int long long

class point {
public:
	int x;
	int y;
	inline point() {

	}
	inline point(int xx, int yy) {
		x = xx;
		y = yy;
	}
};

inline bool comp_x(const point& a, const point& b) { return a.x < b.x; }
inline bool comp_y(const point& a, const point& b) { return a.y < b.y; }

inline int d(const pair& a) {
	int p1 = (a.first.x - a.second.x);
	int p2 = (a.first.y - a.second.y);
	return p1 * p1 + p2 * p2;
}

point Sy[MAXN];

inline pair closest_pairs(point arr1[], int size) {
	if (size <= 1)
		return pair(point(0, 0), point(INT_MAX, INT_MAX));
	int mid_x = arr1[size / 2].x;
	pair left_half = closest_pairs(arr1, size / 2);
	pair right_half = closest_pairs(arr1 + size / 2, (size + 1) / 2);
	int best = std::min(d(left_half), d(right_half));
	pair greatest;
	greatest = d(left_half) < d(right_half) ? left_half : right_half;
	int min_x = mid_x - std::sqrt(best), max_x = mid_x + std::sqrt(best);

	int size_Sy = 0, i = 0, j = size / 2;
	while (size_Sy < size)
		if (i < size / 2 && (j == size || arr1[i].y < arr1[j].y))
			Sy[size_Sy++] = arr1[i++];
		else
			Sy[size_Sy++] = arr1[j++];

	for (int i = 0; i < size; i++)
		arr1[i] = Sy[i];

	size_Sy = 0;
	for (int i = 0; i < size; i++)
		if (arr1[i].x >= min_x && arr1[i].x <= max_x)
			Sy[size_Sy++] = arr1[i];
	int g = best;
	pair b(point(0, 0), point(INT_MAX, INT_MAX));
	for (int i = 0; i < size_Sy - 1; i++)
		for (int j = 0; j < std::min(7LL, size_Sy - i - 1); j++) {
			point m = Sy[i], n = Sy[i + j + 1];
			pair tmp(m, n);
			if (d(tmp) < g)
				b = tmp, g = d(tmp);
		}
	greatest = d(b) < best ? b : greatest;
	return greatest;
}

point sorted_by_x[MAXN];
inline pair closest_pair(point arr[], int& size) {
	for (int i = 0; i < size; i++)
		sorted_by_x[i] = arr[i];

	std::sort(sorted_by_x, sorted_by_x + size, comp_x);

	return closest_pairs(sorted_by_x, size);
}


//	point point_set[MAXN];

/*
signed main() {
	int size;
	std::cin >> size;
	for (int i = 0; i < size; i++)
		std::cin >> point_set[i].x >> point_set[i].y;

	pair best = closest_pair(point_set, size);

	std::cout << d(best) << std::endl;

	return 0;
}
*/