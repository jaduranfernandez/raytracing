#include "../../include/Raytracing/Camera.hpp"

Camera::Camera() {
    focal_length = 1.0;
    viewport_height = 2.0;
    // viewport_width = viewport_height * (double(image_width)/image_height);
    Vector3D position = Point3D(0, 0, 0);
}

Camera::~Camera() {
    // Destructor
}
