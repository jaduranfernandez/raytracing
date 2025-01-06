#ifndef Vector3D_HPP
#define Vector3D_HPP

#include <iostream>
#include <math.h>
#include "Utils.hpp"

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
    static Vector3D random();
    static Vector3D random(double min, double max);
};

// Point3D is just an alias for Vector3D, but useful for geometric clarity in the code.
using Point3D = Vector3D;

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

inline Vector3D random_sample_square(){
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vector3D(random_double() - 0.5, random_double() - 0.5, 0);
}

// Will be used to calculate reflected normal using random noise
inline Vector3D random_unit_vector() {
    while (true) {
        Vector3D p = Vector3D::random(-1,1);
        double lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) // Avoids infinite loops
            return p / sqrt(lensq);
    }
}

inline Vector3D random_on_hemisphere(const Vector3D& normal) {
    Vector3D on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

#endif // Vector3D_HPP
