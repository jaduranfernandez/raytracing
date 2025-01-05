#ifndef Viewport_HPP
#define Viewport_HPP

#include "../Math/Vector3D.hpp"

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
    Viewport();
    ~Viewport();
    void setup(Point3D cameraPos, double focal_length, double aspect_ratio, int window_width, int& window_height);
    Point3D getPixelPos(int row, int col);
};

#endif // Viewport_HPP
