#include "RealVector2D.h"
#include <math.h>

RealVector2D RealVector2D::operator+ (const RealVector2D& other) const {
	return RealVector2D(x + other.x, y + other.y);
}

RealVector2D RealVector2D::operator- (const RealVector2D& other) const {
	return RealVector2D(x - other.x, y - other.y);
}

RealVector2D RealVector2D::operator* (const RealVector2D& other)const {
	return RealVector2D(x * other.x, y * other.y);
}

RealVector2D RealVector2D::operator* (const float m)const {
	return RealVector2D(x * m, y * m);
}

bool RealVector2D::operator== (const RealVector2D& other)const {
	return (x == other.x && y == other.y);
}

bool RealVector2D::operator!= (const RealVector2D& other)const {
	return (x != other.x || y != other.y);
}

float RealVector2D::get_x() const {
	return this->x;
}

float RealVector2D::get_y() const {
	return this->y;
}

RealVector2D RealVector2D::GetUnit()const {
	float mag = Magnitude();
	if (mag == 0) {
		return RealVector2D(0.707, 0.707);
	}
	return RealVector2D(x / mag, y / mag);
}

RealVector2D RealVector2D::GetUnit(const RealVector2D& vec)const {
	float mag = Magnitude(vec);
	if (mag == 0) {
		return RealVector2D(0.707, 0.707);
	}
	return RealVector2D(vec.x / mag, vec.y / mag);
}

RealVector2D RealVector2D::Add(const RealVector2D& vec)const {
	return RealVector2D(x + vec.x, y + vec.y);
}

void RealVector2D::SetMagnitude(float mag) {
	*this = GetUnit() * mag;
}

float RealVector2D::DistanceFrom(const RealVector2D& other)const {
	return Magnitude(*this - other);
}

float RealVector2D::Distance(const RealVector2D& vec1, const RealVector2D& vec2)const {
	return Magnitude(vec1 - vec2);
}

float RealVector2D::Dot(const RealVector2D& vec)const {
	return (this->x * vec.x + this->y * vec.y);
}

float RealVector2D::Dot(const RealVector2D& vec1, const RealVector2D& vec2)const {
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

float RealVector2D::Magnitude() const {
	return sqrt(x * x + y * y);
}

float RealVector2D::Magnitude(const RealVector2D& vec) const {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float RealVector2D::GetAngleFrom(const RealVector2D& vec)const {
	return acos(Dot(vec) / (Magnitude() * Magnitude(vec)));
}

float RealVector2D::Angle()const {
	float angle = atan2(-y, x);
	if (angle < 0) {
		angle = 6.28 + angle;
	}
	return angle;
}

float RealVector2D::GetAngle(const RealVector2D& vec1, const RealVector2D& vec2)const {
	return acos(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
}
