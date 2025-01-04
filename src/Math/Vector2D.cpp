#include "../../include/Math/Vector2D.hpp"


Vector2D::Vector2D() {
    // Constructor
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D::~Vector2D() {
    // Destructor
}

Vector2D Vector2D::operator-() const { return Vector2D(-x, -y); }
double Vector2D::operator[](int i) const { 
    switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("Index out of range");
    }
}
double& Vector2D::operator[](int i) { 
    switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("Index out of range");
    } 
}

Vector2D& Vector2D::operator+=(const Vector2D& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2D& Vector2D::operator*=(double t) {
    x *= t;
    y *= t;
    return *this;
}

Vector2D& Vector2D::operator/=(double t) {
    return *this *= 1/t;
}

double Vector2D::length() const {
    return std::sqrt(length_squared());
}

double Vector2D::length_squared() const {
    return x*x + y*y;
}


