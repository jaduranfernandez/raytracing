#include "../../include/Raytracing/Ray.hpp"

Ray::Ray() {
    // Constructor
}

Ray::Ray(const Point3D& origin, const Vector3D& direction) : orig(origin), dir(direction){

}

Ray::~Ray() {
    // Destructor
}

Point3D Ray::at(double t) const {
    return orig + t*dir;
}

Color Ray::getColor(){
    Vector3D unit_direction = unit_vector(direction());
    auto a = 0.5*(unit_direction.y + 1.0);
    Point3D colorValue = (1.0-a)*Point3D(1.0, 1.0, 1.0) + a*Point3D(0.5, 0.7, 1.0);
    colorValue *= 255;
    return Color(colorValue.x, colorValue.y, colorValue.z);   
}