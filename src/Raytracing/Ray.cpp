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

Color Ray::getSkyboxColor() const{
    Vector3D unit_direction = unit_vector(direction());
    double a = 0.5*(unit_direction.y + 1.0);
    Color originalColor = Color(127, 178, 255);
    Color blendedColor = originalColor.blend(Color::White(), a);
    return blendedColor;
}

double Ray::hitSphere(const Point3D& center, double radius){
    Vector3D oc = center - origin();
    double a = direction().length_squared();
    double h = dot(direction(), oc);
    double c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}
