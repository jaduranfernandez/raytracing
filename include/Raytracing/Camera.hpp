#ifndef Camera_HPP
#define Camera_HPP

#include "../Math/Vector3D.hpp"

class Camera {
public:
    double focal_length;
    Vector3D position;
    Point3D  lookfrom = Point3D(0,0,0);   // Point camera is looking from
    Point3D  lookat   = Point3D(0,0,-1);  // Point camera is looking at
    Vector3D vup      = Vector3D(0,1,0);     // Camera-relative "up" direction

    double vFov = 90;
    Camera();
    ~Camera();
};

#endif // Camera_HPP
