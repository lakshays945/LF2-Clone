#pragma once 

#include <math.h>

class Vector2 {
public:
    float x, y;
    Vector2 operator+ (const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator- (const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator* (const Vector2& other)const {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator* (const float m)const {
        return Vector2(x * m, y * m);
    }

    Vector2 GetUnit()const {
        float mag = Magnitude();
        if (mag == 0) {
            return Vector2(0.707, 0.707);
        }
        return Vector2(x / mag, y / mag);
    }

    Vector2 GetUnit(const Vector2& vec)const {
        float mag = Magnitude(vec);
        if (mag == 0) {
            return Vector2(0.707, 0.707);
        }
        return Vector2(vec.x / mag, vec.y / mag);
    }

    Vector2 Add(const Vector2& vec)const {
        return Vector2(x + vec.x, y + vec.y);
    }

    void SetMagnitude(float mag) {
        *this = GetUnit() * mag;
    }

    bool operator== (const Vector2& other)const {
        return (x == other.x && y == other.y);
    }

    bool operator!= (const Vector2& other)const {
        return (x != other.x || y != other.y);
    }

    float DistanceFrom(const Vector2& other)const {
        return Magnitude(*this - other);
    }

    float Distance(const Vector2& vec1, const Vector2& vec2)const {
        return Magnitude(vec1 - vec2);
    }

    float Dot(const Vector2& vec)const {
        return (this->x * vec.x + this->y * vec.y);
    }

    float Dot(const Vector2& vec1, const Vector2& vec2)const {
        return (vec1.x * vec2.x + vec1.y * vec2.y);
    }

    float Magnitude() const {
        return sqrt(x * x + y * y);
    }

    float Magnitude(const Vector2& vec) const {
        return sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    float GetAngleFrom(const Vector2& vec)const {
        return acos(Dot(vec) / (Magnitude() * Magnitude(vec)));
    }

    float Angle()const {
        float angle = atan2(-y, x);
        if (angle < 0) {
            angle = 6.28 + angle;
        }
        return angle;
    }

    float GetAngle(const Vector2& vec1, const Vector2& vec2)const {
        return acos(Dot(vec1, vec2) / (Magnitude(vec1) * Magnitude(vec2)));
    }

    //constructors
    Vector2(const float x, const float y)
        :x(x), y(y) {}
    Vector2()
        :x(0), y(0) {}
};

Vector2 Infinity(_CRT_INT_MAX, _CRT_INT_MAX);

class Line {
public:
    float a, b, c;

    Vector2 GetIntersection(Line& l1, Line& l2)const {
        float deno = (l1.a * l2.b - l2.a * l1.b);
        if (deno != 0) {
            float X = (l1.b * l2.c - l2.b * l1.c) / deno;
            float Y = -(l1.a * l2.c - l2.a * l1.c) / deno;
            return Vector2(X, Y);
        }
        else {
            return Infinity;
        }
    }

    float GetSlope()const {
        if (b != 0)
            return -a / b;
        return _CRT_INT_MAX;
    }

    float PutPoint(const Vector2& p)const {
        return (p.x * a + p.y * b + c);
    }

    bool CheckParallel(Line& l)const {
        if (GetSlope() == l.GetSlope()) {
            return true;
        }
        return false;
    }

    bool CheckPerpendicular(Line& l)const {
        if ((GetSlope() == _CRT_INT_MAX && l.GetSlope() == 0) || ((l.GetSlope() == _CRT_INT_MAX && GetSlope() == 0))) {
            return true;
        }
        if (GetSlope() * l.GetSlope() == -1) {
            return true;
        }
        return false;
    }

    float DistanceFrom(const Vector2& p)const {
        return abs(PutPoint(p)) / sqrt(a * a + b * b);
    }

    float GetAngle(Line& other)const {
        float m1 = GetSlope();
        float m2 = other.GetSlope();
        return atan2((m1 - m2), (1 + m1 * m2));
    }

    Line(float a, float b, float c)
        :a(a), b(b), c(c) {}

    Line(Vector2& p1, Vector2& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
    }

    Line(const Vector2& p1, const Vector2& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
    }

    Line(float slope, Vector2& p) {
        a = slope;
        b = -1;
        c = p.y - slope * p.x;
    }
    Line()
        :a(1), b(1), c(1) {}
};

bool canIntersect(const Vector2& p1, const Vector2& p2, const Vector2& q) {
    Line l1 = Line(p1, p2);
    if (l1.b == 0) {
        if ((q.y <= p1.y && q.y >= p2.y) || (q.y >= p1.y && q.y <= p2.y)) {
            return true;
        }
        return false;
    }
    float lambda = (p1.x - q.x) * (q.x - p2.x);
    if (lambda >= 0) {
        return true;
    }
    return false;
}
