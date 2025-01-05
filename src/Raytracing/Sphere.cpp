#include "../../include/Raytracing/Sphere.hpp"

Sphere::Sphere(const Point3D center, double radius): center(center), radius(std::fmax(0,radius)) {
    // Constructor
}

Sphere::~Sphere() {
    // Destructor
}

bool Sphere::hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const{
    Vector3D oc = center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - radius*radius;

    double discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;

    double sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;
    Vector3D outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outward_normal);
    
    return true;
}
