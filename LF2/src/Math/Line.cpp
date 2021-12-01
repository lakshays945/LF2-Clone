#include "Line.h"
#include <math.h>

float Line::get_a()const {
	return this->a;
}
float Line::get_b()const {
	return this->b;
}
float Line::get_c()const {
	return this->c;
}
float Line::GetSlope()const {
	if (b != 0)
		return -a / b;
	return _CRT_INT_MAX;
}

bool Line::CheckParallelWith(Line& l)const {
	if (GetSlope() == l.GetSlope()) {
		return true;
	}
	return false;
}

bool Line::CheckPerpendicularTo(Line& l)const {
	if ((GetSlope() == _CRT_INT_MAX && l.GetSlope() == 0) || ((l.GetSlope() == _CRT_INT_MAX && GetSlope() == 0))) {
		return true;
	}
	if (GetSlope() * l.GetSlope() == -1) {
		return true;
	}
	return false;
}

float Line::GetAngle(Line& other)const {
	double m1 = GetSlope();
	double m2 = other.GetSlope();
	return atan2((m1 - m2), (1 + m1 * m2));
}