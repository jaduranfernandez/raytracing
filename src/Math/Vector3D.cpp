#include "../../include/Math/Vector3D.hpp"


Vector3D::Vector3D() {
    // Constructor
}

Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D() {
    // Destructor
}

Vector3D Vector3D::random() {
    return Vector3D(random_double(), random_double(), random_double());
}

Vector3D Vector3D::random(double min, double max) {
    return Vector3D(random_double(min,max), random_double(min,max), random_double(min,max));
}

Vector3D Vector3D::operator-() const { return Vector3D(-x, -y, -z); }
double Vector3D::operator[](int i) const { 
    switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("Index out of range");
    } 
}
double& Vector3D::operator[](int i) { 
    switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("Index out of range");
    } 
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3D& Vector3D::operator*=(double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vector3D& Vector3D::operator/=(double t) {
    return *this *= 1/t;
}

double Vector3D::length() const {
    return std::sqrt(length_squared());
}

double Vector3D::length_squared() const {
    return x*x + y*y + z*z;
}

