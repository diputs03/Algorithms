#include "Geometry.h"

std::pair<answers, std::vector<point_2D>> line_circle_intersect(circle ci, line l) {
	double a = l.a, b = l.b, c = l.c;
	double x = ci.point.x, y = ci.point.y, r = ci.radius;
	double A = a * a + b * b;
	double B = 2 * a * b * y - 2 * a * c - 2 * b * b * x;
	double C = b * b * x * x + b * b * y * y - 2 * b * c * y + c * c - b * b * r * r;
	double D = B * B - 4 * A * C;
	double x1, x2, y1, y2;
	if (!b) {
		x1 = c / a;
		if (std::abs(x - x1) > r)
			return std::make_pair(disjoint, std::vector<point_2D>{});
		if (!(x1 - r - x) || !(x1 + r - x))
			return std::make_pair(tangent, std::vector<point_2D>{point_2D(x1, y)});
		double dx = std::abs(x1 - x);
		double dy = std::sqrt(r * r - dx * dx);
		return std::make_pair(intersect, std::vector<point_2D>{point_2D(x1, y + dy), point_2D(x1, y - dy)});
	}
	else if (!D) {
		x1 = -B / (2 * A);
		y1 = (c - a * x1) / b;
		return std::make_pair(tangent, std::vector<point_2D>{point_2D(x1, y1)});
	}
	else if (D < 0) {
		return std::make_pair(disjoint, std::vector<point_2D>{});
	}
	else {
		D = std::sqrt(D);
		x1 = (-B + D) / (2 * A);
		y1 = (c - a * x1) / b;
		x2 = (-B - D) / (2 * A);
		y2 = (c - a * x2) / b;
		return std::make_pair(intersect, std::vector<point_2D>{point_2D(x1, y1), point_2D(x2, y2)});
	}
}