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
    if(hitSphere(Point3D(0,0,-1), 0.5))
        return Color::Red();
    Vector3D unit_direction = unit_vector(direction());
    double a = 0.5*(unit_direction.y + 1.0);
    Point3D colorValue = (1.0-a)*Point3D(1.0, 1.0, 1.0) + a*Point3D(0.5, 0.7, 1.0);
    colorValue *= 255;
    return Color(colorValue.x, colorValue.y, colorValue.z);   
}

bool Ray::hitSphere(const Point3D& center, double radius){
    Vector3D oc = center - origin();
    auto a = dot(direction(), direction());
    auto b = -2.0 * dot(direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
