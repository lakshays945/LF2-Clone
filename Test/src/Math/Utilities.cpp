#include "Utilities.h"
#include <math.h>

RealVector2D IntersectTwoLines(Line& l1, Line& l2){

    float l1_a = l1.get_a();
    float l1_b = l1.get_b();
    float l1_c = l1.get_c();
    float l2_a = l2.get_a();
    float l2_b = l2.get_b();
    float l2_c = l2.get_c();

    float deno = (l1_a * l2_b - l2_a * l1_b);
    if (deno != 0) {
        float X = (l1_b * l2_c - l2_b * l1_c) / deno;
        float Y = -(l1_a * l2_c - l2_a * l1_c) / deno;
        return RealVector2D(X, Y);
    }
    else {
        return Infinity;
    }
}
float LineDistanceFromPoint2d(const Line l,const RealVector2D& p){
    float line_a = l.get_a();
    float line_b = l.get_b();
    float line_c = l.get_c();
    float point_x = p.get_x();
    float point_y = p.get_y();

    float putted_point = (point_x * line_a + point_y * line_b + line_c);
    return fabs(putted_point) / sqrt(line_a* line_a + line_b* line_b);
}
Line LineFromPoints(const RealVector2D& p1, const RealVector2D& p2) {
    float a = p2.get_y() - p1.get_y();
    float b = p1.get_x() - p2.get_x();
    float c = p2.get_x() * p1.get_y() - p1.get_x() * p2.get_y();
    return Line(a, b, c);
}
Line LineFromPointAndSlope(float slope, RealVector2D& p) {
    float a = slope;
    float b = -1;
    float c = p.get_y() - slope * p.get_x();
    return Line(a, b, c);
}
bool LineSegmentCanIntersect(const RealVector2D& p1, const RealVector2D& p2, const RealVector2D& q) {

    Line l1 = LineFromPoints(p1, p2);
    if (l1.get_b() == 0) {
        if ((q.get_y() <= p1.get_y() && q.get_y() >= p2.get_y()) || (q.get_y() >= p1.get_y() && q.get_y() <= p2.get_y())) {
            return true;
        }
        return false;
    }
    float lambda = (p1.get_x() - q.get_x()) * (q.get_x() - p2.get_x());

    if (lambda >= 0) 
        return true;
   
    return false;
}
