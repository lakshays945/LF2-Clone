#pragma once

class RealVector2D {
	float x, y;

public:

	//constructors
	RealVector2D(const float x, const float y)
		:x(x), y(y) {}
	RealVector2D()
		:x(0), y(0) {}

	//operator overloading
	RealVector2D operator+ (const RealVector2D& other)const;
	RealVector2D operator- (const RealVector2D& other)const;
	RealVector2D operator* (const RealVector2D& other)const;
	RealVector2D operator* (const float m)const;
	bool operator== (const RealVector2D& other)const;
	bool operator!= (const RealVector2D& other)const;

	//methods
	float get_x() const;
	float get_y() const;
	RealVector2D GetUnit()const;
	RealVector2D GetUnit(const RealVector2D& vec)const;
	RealVector2D Add(const RealVector2D& vec)const;

	void SetMagnitude(float mag);
	float DistanceFrom(const RealVector2D& other)const;
	float Distance(const RealVector2D& vec1, const RealVector2D& vec2)const;
	float Dot(const RealVector2D& vec)const;
	float Dot(const RealVector2D& vec1, const RealVector2D& vec2)const;
	float Magnitude() const;
	float Magnitude(const RealVector2D& vec) const;
	float GetAngleFrom(const RealVector2D& vec)const;
	float Angle()const;
	float GetAngle(const RealVector2D& vec1, const RealVector2D& vec2)const;

};
