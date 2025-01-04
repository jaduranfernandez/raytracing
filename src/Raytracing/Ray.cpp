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
    double t = hitSphere(Point3D(0,0,-1), 0.5);
    if (t > 0.0) {
        Vector3D N = unit_vector(at(t) - Vector3D(0,0,-1));
        Point3D colorValue = 0.5*Point3D(N.x+1, N.y+1, N.z+1);
        colorValue *= 255;
        return Color(colorValue.x, colorValue.y, colorValue.z);   
    }

    Vector3D unit_direction = unit_vector(direction());
    double a = 0.5*(unit_direction.y + 1.0);
    Point3D colorValue = (1.0-a)*Point3D(1.0, 1.0, 1.0) + a*Point3D(0.5, 0.7, 1.0);
    colorValue *= 255;
    return Color(colorValue.x, colorValue.y, colorValue.z);   
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
