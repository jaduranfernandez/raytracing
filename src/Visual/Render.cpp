#include "../../include/Visual/Render.hpp"


Render::Render(){
    cameraPos = Vector3D(0, 0, 0);
};

bool Render::init(int width, double aspectRatio){
    this->viewport.setup(this->cameraPos, 1.0, aspectRatio, width, height);
    return SDLRenderer::init(width, height);
};


void Render::drawRays(const GeoBody& world){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point3D pixelCenter = this->viewport.getPixelPos(x, y);
            Vector3D rayDirection = pixelCenter - cameraPos;
            Ray r(cameraPos, rayDirection);
            Color pixelColor = calculateRayColor(r, world);
            drawPixel(x, y, pixelColor);
        }
    }
}

void Render::destroy(){
    SDLRenderer::destroy();
}

Color Render::calculateRayColor(const Ray& ray, const GeoBody& world){
    HitRecord rec;
    if (world.hit(ray, Interval(0, infinity), rec)) {
        Vector3D direction = random_on_hemisphere(rec.normal);
        // return 0.5 * ray_color(ray(rec.p, direction), world);
        // return 127.5 * (rec.normal + Point3D(1,1,1)); // 127.5 = 255/2
        return 0.5 * calculateRayColor(Ray(rec.p, direction), world); // 127.5 = 255/2
    }
    return ray.getSkyboxColor();
}

