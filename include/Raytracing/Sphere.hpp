#ifndef Sphere_HPP
#define Sphere_HPP

#include "GeoBody.hpp"

class Sphere: public GeoBody {
private:
    Point3D center;
    double radius;
public:
    Sphere(const Point3D center, double radius);
    ~Sphere();
    bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;
};

#endif // Sphere_HPP
