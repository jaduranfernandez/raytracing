#ifndef Sphere_HPP
#define Sphere_HPP

#include "GeoBody.hpp"

class Sphere: public GeoBody {
private:
    Point3D center;
    double radius;
    shared_ptr<Material> mat;
public:
    Sphere(const Point3D center, double radius);
    ~Sphere();
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

#endif // Sphere_HPP
