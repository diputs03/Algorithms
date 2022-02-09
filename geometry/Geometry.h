#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <stack>
#include <list>

class point_2D {
public:
	double x;
	double y;
	point_2D() {
		x = INT_MAX;
		y = INT_MAX;
	}
	point_2D(double xx, double yy) {
		x = xx;
		y = yy;
	}
	friend double dist(point_2D a, point_2D b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	friend point_2D operator+(point_2D a, point_2D b) {
		return point_2D(a.x + b.x, a.y + b.y);
	}
	friend point_2D operator-(point_2D a, point_2D b) {
		return point_2D(a.x - b.x, a.y - b.y);
	}
	friend double dot_product(point_2D a, point_2D b) {
		return (a.x * b.x) + (a.y * b.y);
	}
	friend bool operator==(point_2D a, point_2D b) {
		return (a.x == b.x) && (a.y == b.y);
	}
	friend bool operator!=(point_2D a, point_2D b) {
		return !(a == b);
	}
};

class vector_2D {
public:
	point_2D point;
	vector_2D(point_2D a) {
		point = a;
	}
	double length() {
		return std::sqrt(point.x * point.x + point.y * point.y);
	}
	friend double dot_product(vector_2D a, vector_2D b) {
		return (a.point.x * b.point.x) + (a.point.y * b.point.y);
	}
	friend double angle(vector_2D a, vector_2D b) {
		return std::acos(dot_product(a, b) / (a.length() * b.length()));
	}
};

class point_3D {
public:
	double x;
	double y;
	double z;
	point_3D() {
		x = INT_MAX;
		y = INT_MAX;
		z = INT_MAX;
	}
	point_3D(double xx, double yy, double zz) {
		x = xx;
		y = yy;
		z = zz;
	}
	friend double dist(point_3D a, point_3D b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}
	friend point_3D operator+(point_3D a, point_3D b) {
		return point_3D(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend point_3D operator-(point_3D a, point_3D b) {
		return point_3D(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	friend double dot_product(point_3D a, point_3D b) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}
	friend bool operator==(point_3D a, point_3D b) {
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
	}
	friend bool operator!=(point_3D a, point_3D b) {
		return !(a == b);
	}
	friend point_3D cross_product(point_3D v1, point_3D v2) {
		double v3x = v1.y * v2.z - v1.z * v2.y;
		double v3y = v1.z * v2.x - v1.x * v2.z;
		double v3z = v1.x * v2.y - v1.y * v2.x;
		return point_3D(v3x, v3y, v3z);
	}
};

class vector_3D {
public:
	point_3D point;
	double length() {
		return std::sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
	}
	friend double dot_product(vector_3D a, vector_3D b) {
		return (a.point.x * b.point.x) + (a.point.y * b.point.y) + (a.point.z * b.point.z);
	}
	friend double angle(vector_3D a, vector_3D b) {
		return std::acos(dot_product(a, b) / (a.length() * b.length()));
	}
};

enum answers {
	disjoint, infinity, containing, intersect, tangent
};

const static double eps = 1e-9;
class circle {
public:
	point_2D rotate_point(point_2D p, double angle) {
		double x = p.x - this->point.x;
		double y = p.y - this->point.y;
		double x_r = x * std::cos(angle) + y * std::sin(angle);
		double y_r = y * std::cos(angle) + x * std::sin(angle);
		return point_2D(this->point.x + x, this->point.y + y);
	}
	point_2D point;
	double radius;
	double area() {
		return radius * radius * std::acos(-1);
	}
};

class line {
public:
	//	ax + by = c
	double a, b, c;
	line(point_2D a, point_2D b) {
		this->a = a.y - b.y;
		this->b = b.x - a.x;
		this->c = b.x * a.y - a.x * b.y;
		normalise();
	}
	void normalise() {
		if (abs(b) == 0) {
			c /= a;
			a = 1;
			b = 0;
		}
		else {
			a = (abs(a) == 0) ? 0 : a / b;
			c /= b;
			b = 1;
		}
	}
	line slope_point_to_line(double slope, point_2D pt) {
		point_2D p2;
		if (slope == INT_MAX || slope == -INT_MAX)
			p2 = point_2D(pt.x, pt.y + 1);
		else
			p2 = point_2D(pt.x + 1, pt.y + slope);
		return line(pt, p2);
	}
	line perpendicular_bisector(point_2D a, point_2D b) {
		point_2D mid = point_2D((a.x + b.x) / 2, (a.y + b.y) / 2);
		double perp_slope = (a.x - b.x) / (a.y - b.y);

		if (b.y - a.y == 0)
			perp_slope = INT_MAX;
		else if (a.x - b.x == 0)
			perp_slope = 0;
		return slope_point_to_line(perp_slope, mid);
	}
	friend point_2D intersect(line l1, line l2) {
		double x = INT_MAX, y = INT_MAX;
		if (!l1.b) {
			x = l1.c / l1.a;
			y = (l2.c - l2.a * x) / l2.b;
		}
		else if (!l2.b) {
			x = l2.c / l2.a;
			y = (l1.c - l1.a * x) / l1.b;
		}
		else if (!l1.a) {
			y = l1.c / l1.b;
			x = (l2.c - l2.b * y) / l2.a;
		}
		else if (!l2.a) {
			y = l2.c / l2.b;
			x = (l1.c - l1.b * y) / l1.a;
		}
		else {
			x = (l1.c - l2.c) / (l1.a - l2.a);
			y = (l1.c - l1.a * x) / l1.b;
		}
		return point_2D(x, y);
	}
};

class triangle {
public:
	point_2D a, b, c;
	triangle(point_2D a, point_2D b, point_2D c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
	double area() {
		return std::abs(dot_product(a - b, b - c) / 2.0);
	}
	bool point_inside_triangle(point_2D p) {
		bool dir1 = collinear(a, b, p) < 0;
		bool dir2 = collinear(b, c, p) < 0;
		bool dir3 = collinear(c, a, p) < 0;
		return dir1 == dir2 == dir3;
	}
};

double collinear(point_2D a, point_2D b, point_2D c) {
	double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (area < eps)
		return 0;
	return area;
}

double coplanar(point_3D a, point_3D b, point_3D c, point_3D d) {
	point_3D v1(b.x - a.x, b.y - a.y, b.z - a.z);
	point_3D v2(c.x - a.x, c.y - a.y, c.z - a.z);
	point_3D v3(d.x - a.x, d.y - a.y, d.z - a.z);

	point_3D v4 = cross_product(v1, v2);

	return std::abs(dot_product(v3, v4));
}


int orientation(point_2D a, point_2D b, point_2D c) {
	triangle t(a, b, c);
	double val = t.area();
	if (val == 0)
		return 0;
	return (val > 0) ? -1 : 1;
}