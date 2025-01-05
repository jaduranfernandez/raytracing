#ifndef GeoBody_HPP
#define GeoBody_HPP


#include "../Math/Utils.hpp"
#include "Ray.hpp"
#include "../Math/Interval.hpp"

class HitRecord {
  public:
    Point3D p;
    Vector3D normal;
    double t;
    bool isFrontFace;
    void setFaceNormal(const Ray& r, const Vector3D& outward_normal);
};

class GeoBody {
  public:
    virtual ~GeoBody() = default;
    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};


#endif // GeoBody_HPP
