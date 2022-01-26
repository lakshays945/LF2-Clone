#pragma once

class Line {
    float a, b, c;
public:

    //constructors
    Line(float a, float b, float c)
        :a(a), b(b), c(c) {}
    Line()
        :a(1), b(1), c(1) {}

    //methods
    float get_a()const;
    float get_b()const;
    float get_c()const;
    float GetSlope()const;
    bool CheckParallelWith(Line& l)const;
    bool CheckPerpendicularTo(Line& l)const;
    float GetAngle(Line& other)const;

};
