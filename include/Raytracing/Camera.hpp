#ifndef Camera_HPP
#define Camera_HPP

#include "../Math/Vector3D.hpp"

class Camera {
private:
    double focal_length;
    double viewport_height;
    double viewport_width;
    Vector3D position;

public:
    Camera();
    ~Camera();
};

#endif // Camera_HPP
