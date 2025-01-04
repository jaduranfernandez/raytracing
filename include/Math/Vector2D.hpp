#ifndef Vector2D_HPP
#define Vector2D_HPP

#include <iostream>
#include <math.h>

class Vector2D {
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double x, double y);
    ~Vector2D();

    // Operators
    Vector2D operator-() const;
    double operator[](int i) const;
    double& operator[](int i);
    Vector2D& operator+=(const Vector2D& v);
    Vector2D& operator*=(double t);
    Vector2D& operator/=(double t);
    double length() const;
    double length_squared() const;
};

// point2 is just an alias for Vector2D, but useful for geometric clarity in the code.
using point2 = Vector2D;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
    return out << v.x << ' ' << v.y;
}

inline Vector2D operator+(const Vector2D& u, const Vector2D& v) {
    return Vector2D(u.x + v.x, u.y + v.y);
}

inline Vector2D operator-(const Vector2D& u, const Vector2D& v) {
    return Vector2D(u.x - v.x, u.y - v.y);
}

inline Vector2D operator*(const Vector2D& u, const Vector2D& v) {
    return Vector2D(u.x * v.x, u.y * v.y);
}

inline Vector2D operator*(double t, const Vector2D& v) {
    return Vector2D(t*v.x, t*v.y);
}

inline Vector2D operator*(const Vector2D& v, double t) {
    return t * v;
}

inline Vector2D operator/(const Vector2D& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector2D& u, const Vector2D& v) {
    return u.x * v.x + u.y * v.y;
}

inline Vector2D unit_vector(const Vector2D& v) {
    return v / v.length();
}
#endif // Vector2D_HPP
