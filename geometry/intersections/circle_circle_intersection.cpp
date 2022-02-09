#include "Geometry.h"

std::pair<answers, double> intersection_area(circle a, circle b) {
	circle c, C;
	if (a.radius < b.radius)
		c = a, C = b;
	else
		c = b, C = a;
	std::pair<answers, std::vector<point_2D>> intersection = intersection_point(a, b);
	if (intersection.first == containing)
		return std::make_pair(containing, std::acos(-1) * c.radius * c.radius);
	else if (intersection.first == disjoint)
		return std::make_pair(disjoint, 0);
	else if (intersection.first == tangent)
		if (dist(a.point, b.point) < C.radius)
			return std::make_pair(tangent, std::acos(-1) * c.radius * c.radius);
		else
			return std::make_pair(tangent, 0);
	else {
		double d = dist(a.point, b.point);
		double p1 = c.radius * c.radius * std::acos((d * d + c.radius * c.radius - C.radius * C.radius) / (2 * d * c.radius));
		double p2 = C.radius * C.radius * std::acos((d * d - c.radius * c.radius + C.radius * C.radius) / (2 * d * c.radius));
		double p3 = 0.5 * std::sqrt((-d + c.radius + C.radius) * (d + c.radius - C.radius) * (d - c.radius + C.radius) * (d + c.radius + C.radius));
		return std::make_pair(intersect, p1 + p2 + p3);
	}
}
std::pair<answers, std::vector<point_2D>> intersection_point(circle a, circle b) {
	circle c, C;
	if (a.radius < b.radius)
		c = a, C = b;
	else
		c = b, C = a;
	double distance = dist(c.point, C.point);
	if (distance < eps && abs(c.radius - C.radius) < eps)
		return std::make_pair(infinity, std::vector<point_2D>{});
	if (c.radius + distance < C.radius)
		return std::make_pair(containing, std::vector<point_2D>{});
	if (c.radius + C.radius < distance)
		return std::make_pair(disjoint, std::vector<point_2D>{});

	double x = ((c.point.x - C.point.x) / distance) * C.radius + C.point.x;
	double y = ((c.point.y - C.point.y) / distance) * C.radius + C.point.y;

	if (std::abs(c.radius + C.radius - distance) < eps || std::abs(C.radius - (c.radius + distance)) < eps)
		return std::make_pair(tangent, std::vector<point_2D>{point_2D(x, y)});

	double angle = std::acos((c.radius * c.radius - distance * distance - C.radius * C.radius) / (-2.0 * distance * C.radius));

	return std::make_pair(intersect, std::vector<point_2D>{C.rotate_point(point_2D(x, y), angle), C.rotate_point(point_2D(x, y), -angle)});
}

double intersection_area(circle center, point_2D a, point_2D b) {
	double half_circle = center.area() / 2;
	double three_p = triangle(center.point, a, b).area();
	double pizza = center.area() * angle(vector_2D(a - center.point), vector_2D(b - center.point));
	return center.area() - (half_circle + three_p + pizza);
}