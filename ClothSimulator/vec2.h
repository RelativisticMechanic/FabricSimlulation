#ifndef VEC2_H
#define VEC2_H
#include <cmath>

class vec2
{
public:
    vec2() : e{ 0,0 } {}
    vec2(double e0, double e1) : e{ e0, e1 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }

    vec2 operator-() const { return vec2(-e[0], -e[1]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec2& operator+=(const vec2& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        return *this;
    }

    vec2 operator+(const vec2& v) { return vec2(this->e[0] + v[0], this->e[1] + v[1]); }
    vec2 operator-(const vec2& v) { return vec2(this->e[0] - v[0], this->e[1] - v[1]); }
    vec2 operator*(const double t) { return vec2(t * e[0], t * e[1]); }
    vec2 operator/(const double t) { return vec2(e[0] / t, e[1] / t);  }

    vec2& operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        return *this;
    }

    vec2& operator/=(const double t)
    {
        e[0] /= t;
        e[1] /= t;
        return *this;
    }

    double length() const
    {
        return sqrt(sqlength());
    }

    double sqlength() const
    {
        return e[0] * e[0] + e[1] * e[1];
    }
public:
    double e[2];
};

typedef vec2 Force;
#endif