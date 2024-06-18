#include "vector2.hpp"

const double Vector2::norm() const {
    const Vector2& v = *this;
    return sqrt(dotProduct(v, v));
}

void Vector2::normalize() {
    const double n = norm();
    if (n > 0.0 && n != 1.0) {
        *this /= n;
    }
}

const Vector2 Vector2::zero() {
    return { 0.0, 0.0 };
}

const Vector2 Vector2::i() {
    return { 1.0, 0.0 };
}

const Vector2 Vector2::j() {
    return { 0.0, 1.0 };
}

const double Vector2::angle(const Vector2& v1, const Vector2& v2) {
    const double norm = v1.norm() * v2.norm();
    const double dot = dotProduct(v1, v2);
    return acos(dot / norm);
}

const double Vector2::angleDegrees(const Vector2& v1, const Vector2& v2) {
    return angle(v1, v2) * 180.0 / M_PI;
}

const double Vector2::distance(const Vector2& v1, const Vector2& v2) {
    const double dx = v1.x - v2.x;
    const double dy = v1.y - v2.y;
    return sqrt(dx * dx + dy * dy);
}

const Vector2 Vector2::reflect(const Vector2& v1, const Vector2& v2) {
    Vector2 n = v1 - Vector2::dotProduct(v1, v2) * v2;
    n.normalize();

    return v1 - 2.0 * Vector2::dotProduct(v1, n) * n;
}

const double Vector2::dotProduct(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

const Vector2 Vector2::scalarProduct(const Vector2& v, const double a) {
    return { v.x * a, v.y * a };
}

const Vector2 Vector2::sum(const Vector2& v1, const Vector2& v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}

const Vector2 Vector2::subtract(const Vector2& v1, const Vector2& v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

const Vector2 operator*(const Vector2& v, const double a) {
    return Vector2::scalarProduct(v, a);
}

const Vector2 operator*(const double a, const Vector2& v) {
    return Vector2::scalarProduct(v, a);
}

const Vector2 operator/(const Vector2& v, const double a) {
    return Vector2::scalarProduct(v, 1 / a); 
}

const Vector2 operator/(const double a, const Vector2& v) {
    return Vector2::scalarProduct(v, 1 / a); 
}

const Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return Vector2::sum(v1, v2);
}

const Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return Vector2::subtract(v1, v2);
}

void operator*=(Vector2& v, const double a) {
    v = v * a;
}

void operator/=(Vector2& v, const double a) {
    v = v / a;
}

void operator+=(Vector2& v1, const Vector2& v2) {
    v1 = v1 + v2;
}

void operator-=(Vector2& v1, const Vector2& v2) {
    v1 = v1 - v2;
}