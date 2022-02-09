#include "Geometry.h"

point_2D center;

bool cmp(point_2D& a, point_2D& b) {
	double a1 = ((std::atan2(a.x - center.x, a.y - center.y) / std::acos(-1) * 180) + 360) / 360;
	double a2 = ((std::atan2(b.x - center.x, b.y - center.y) / std::acos(-1) * 180) + 360) / 360;
	return a1 < a2;
}

std::vector<point_2D> sort_cw(std::vector<point_2D> pts) {
	int l = pts.size();
	double centroid_x = 0;
	double centroid_y = 0;
	for (int i = 0; i < l; i++) {
		centroid_x += pts[i].x;
		centroid_y += pts[i].y;
	}
	centroid_x /= l;
	centroid_y /= l;
	center = point_2D(centroid_x, centroid_y);
	std::sort(pts.begin(), pts.end(), cmp);
	return pts;
}

point_2D intersect(point_2D a, point_2D b, point_2D c, point_2D d) {
	double a1 = b.y - a.y, a2 = d.y - c.y, b1 = a.x - b.x, b2 = c.x - d.x;
	double c1 = -(a.x * b.y - b.x * a.y), c2 = -(c.x * d.y - d.x * c.y);
	double det = a1 * b2 - a2 * b1;
	double x = -(c1 * b2 - c2 * b1) / det, y = -(a1 * c2 - a2 * c1) / det;
	return point_2D(x, y);
}

std::vector<point_2D> cut(std::vector<point_2D> pts, point_2D a, point_2D b) {
	int n = pts.size();
	std::vector<point_2D> res;
	for (int i = 0, j = n - 1; i < n; j = i++) {
		int d1 = orientation(a, b, pts[j]);
		int d2 = orientation(a, b, pts[i]);
		if (d1 >= 0)
			res.push_back(pts[j]);
		if (d1 * d2 < 0)
			res.push_back(intersect(a, b, pts[j], pts[i]));
	}
	return res;
}