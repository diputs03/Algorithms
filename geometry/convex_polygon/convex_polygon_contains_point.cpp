#include "Geometry.h"

bool contains_point(std::vector<point_2D> hull, point_2D p) {

    point_2D p0 = hull[0];
    int lo = 1, hi = hull.size() - 2, mid = (lo + hi) >> 1;

    while (lo != hi) {
        point_2D p1 = hull[mid];
        double sign = collinear(p0, p1, p);
        if (sign >= 0) lo = mid;
        else if (sign < 0) hi = mid;
        mid = (lo + hi) >> 1;
        if (hi - lo == 1) {
            if (collinear(p0, hull[hi], p) >= 0) lo = hi;
            else hi = lo;
        }
    }

    point_2D p1 = hull[lo], p2 = hull[lo + 1];
    double boundSign = collinear(p1, p2, p);
    double segSign1 = collinear(p0, p1, p);
    double segSign2 = collinear(p0, p2, p);

    return (boundSign >= 0 && segSign1 >= 0 && segSign2 <= 0);
}
