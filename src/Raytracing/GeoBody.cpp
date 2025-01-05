#include "../../include/Raytracing/GeoBody.hpp"


void HitRecord::setFaceNormal(const Ray& r, const Vector3D& outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    isFrontFace = dot(r.direction(), outward_normal) < 0;
    normal = isFrontFace ? outward_normal : -outward_normal;
}