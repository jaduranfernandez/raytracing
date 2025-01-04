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