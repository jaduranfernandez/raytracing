#include "../../include/Visual/Viewport.hpp"

Viewport::Viewport() {
    aspect_ratio = 16.0 / 9.0;
}

Viewport::~Viewport() {
    // Destructor
}

void Viewport::setup(Point3D cameraPos, double focal_length, double aspect_ratio, int window_width, int& window_height){
    // Calculate the image height, and ensure that it's at least 1.
    this->aspect_ratio = aspect_ratio;
    window_height = int(window_width / aspect_ratio);
    std::cout<<"Width: "<<window_width<<"| Aspect Ratio: "<<aspect_ratio<<" | Height: "<<window_height<<std::endl;
    window_height = (window_height < 1) ? 1 : window_height;

    viewport_height = 2.0;
    viewport_width = viewport_height * (double(window_width)/window_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    viewport_u = Vector3D(viewport_width, 0, 0);
    viewport_v = Vector3D(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / window_width;
    pixel_delta_v = viewport_v / window_height;

    // Calculate the location of the upper left pixel.
    viewport_upper_left = cameraPos - Vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_pos = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Point3D Viewport::getPixelPos(int col, int row){
    return pixel00_pos + (col * pixel_delta_u) + (row * pixel_delta_v);
}