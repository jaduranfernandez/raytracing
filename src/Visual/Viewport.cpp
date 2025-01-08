#include "../../include/Visual/Viewport.hpp"

Viewport::Viewport() {
    aspect_ratio = 16.0 / 9.0;
}

Viewport::~Viewport() {
    // Destructor
}

void Viewport::setup(Camera c, double aspect_ratio, int window_width, int& window_height){
    // Calculate the image height, and ensure that it's at least 1.
    this->aspect_ratio = aspect_ratio;
    window_height = int(window_width / aspect_ratio);
    window_height = (window_height < 1) ? 1 : window_height;

    auto theta = degrees2radians(c.vFov);
    auto h = std::tan(theta/2);
    viewport_height = 2 * h * c.focal_length;
    // viewport_height = 2.0;
    viewport_width = viewport_height * (double(window_width)/window_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    Vector3D w = unit_vector(c.lookfrom - c.lookat);
    Vector3D u = unit_vector(cross(c.vup, w));
    Vector3D v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / window_width;
    pixel_delta_v = viewport_v / window_height;

    // Calculate the location of the upper left pixel.
    viewport_upper_left = c.lookfrom - (c.focal_length * w) - viewport_u/2 - viewport_v/2;
    pixel00_pos = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Point3D Viewport::getPixelPos(int col, int row){
    return pixel00_pos + (col * pixel_delta_u) + (row * pixel_delta_v);
}

Point3D Viewport::getPixelPosOffset(int col, int row, double xOffset, double yOffset){
    return pixel00_pos + ((col + xOffset) * pixel_delta_u) + ((row + yOffset) * pixel_delta_v);
}
