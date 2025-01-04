#ifndef Vector3D_HPP
#define Vector3D_HPP

#include <iostream>
#include <math.h>

class Vector3D {
public:
    double x;
    double y;
    double z;

    Vector3D();
    Vector3D(double x, double y, double z);
    ~Vector3D();

    // Operators
    Vector3D operator-() const;
    double operator[](int i) const;
    double& operator[](int i);
    Vector3D& operator+=(const Vector3D& v);
    Vector3D& operator*=(double t);
    Vector3D& operator/=(double t);
    double length() const;
    double length_squared() const;
};

// point3 is just an alias for Vector3D, but useful for geometric clarity in the code.
using point3 = Vector3D;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vector3D& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vector3D operator+(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector3D operator-(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vector3D operator*(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vector3D operator*(double t, const Vector3D& v) {
    return Vector3D(t*v.x, t*v.y, t*v.z);
}

inline Vector3D operator*(const Vector3D& v, double t) {
    return t * v;
}

inline Vector3D operator/(const Vector3D& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector3D& u, const Vector3D& v) {
    return u.x * v.x
         + u.y * v.y
         + u.z * v.z;
}

inline Vector3D cross(const Vector3D& u, const Vector3D& v) {
    return Vector3D(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

inline Vector3D unit_vector(const Vector3D& v) {
    return v / v.length();
}

#endif // Vector3D_HPP
