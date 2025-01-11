#ifndef Viewport_HPP
#define Viewport_HPP

#include "../Math/Vector3D.hpp"
#include "../Raytracing/Camera.hpp"

class Viewport {
private:
    Vector3D viewport_u;
    Vector3D viewport_v;

public:
    double viewport_width;
    double viewport_height;
    double aspect_ratio;
    Vector3D pixel_delta_u;
    Vector3D pixel_delta_v;
    Point3D viewport_upper_left;
    Point3D pixel00_pos;
    Vector3D defocus_disk_u;       // Defocus disk horizontal radius
    Vector3D defocus_disk_v;       // Defocus disk vertical radius
    Viewport();
    ~Viewport();
    void setup(Camera c, double aspect_ratio, int window_width, int& window_height);
    Point3D getPixelPos(int row, int col);
    Point3D getPixelPosOffset(int row, int col, double xOffset, double yOffset);
};

#endif // Viewport_HPP
