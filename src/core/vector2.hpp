#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

struct Vector2 {
public:
    double x, y;

public:
    const double norm() const;
    void normalize();

    static const Vector2 zero();
    static const Vector2 i();
    static const Vector2 j();

    static const double angle(const Vector2& v1, const Vector2& v2);
    static const double angleDegrees(const Vector2& v1, const Vector2& v2);
    static const double distance(const Vector2& v1, const Vector2& v2);
    static const Vector2 reflect(const Vector2& v1, const Vector2& v2);

// Mathematical operations
    static const double dotProduct(const Vector2& v1, const Vector2& v2);
    static const Vector2 scalarProduct(const Vector2& v, const double a);
    static const Vector2 sum(const Vector2& v1, const Vector2& v2);
    static const Vector2 subtract(const Vector2& v1, const Vector2& v2);

// Operators
    friend const Vector2 operator*(const Vector2& v, const double a);
    friend const Vector2 operator*(const double a, const Vector2& v);
    friend const Vector2 operator/(const Vector2& v, const double a);
    friend const Vector2 operator/(const double a, const Vector2& v);
    friend const Vector2 operator+(const Vector2& v1, const Vector2& v2);
    friend const Vector2 operator-(const Vector2& v1, const Vector2& v2);

    friend void operator*=(Vector2& v, const double a);
    friend void operator/=(Vector2& v, const double a);
    friend void operator+=(Vector2& v1, const Vector2& v2);
    friend void operator-=(Vector2& v1, const Vector2& v2);
};