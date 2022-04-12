#pragma once
#include "Line.h"
#include "RealVector2D.h"
#include <corecrt.h>

#define DEFAULT_GRAVITY_CONSTANT 980
#define Infinity RealVector2D(_CRT_INT_MAX, _CRT_INT_MAX)
#define GravityVector RealVector2D(0,DEFAULT_GRAVITY_CONSTANT)

RealVector2D IntersectTwoLines(Line& l1, Line& l2);
float LineDistanceFromPoint2d(const Line l, const RealVector2D& p);
Line LineFromPoints(const RealVector2D& p1, const RealVector2D& p2);
Line LineFromPointAndSlope(float slope, RealVector2D& p);
bool LineSegmentCanIntersect(const RealVector2D& p1, const RealVector2D& p2, const RealVector2D& q);