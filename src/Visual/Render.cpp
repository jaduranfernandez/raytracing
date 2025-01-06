#include "../../include/Visual/Render.hpp"


Render::Render(){
    cameraPos = Vector3D(0, 0, 0);
};

bool Render::init(int width, double aspectRatio, int samples, int maxDepth){
    this->samplesPerPixel = samples;
    this->maxDepth = maxDepth;
    this->viewport.setup(this->cameraPos, 1.0, aspectRatio, width, height);
    pixelSampleScale = 1.0 / samplesPerPixel;
    return SDLRenderer::init(width, height);
};


void Render::drawRays(const GeoBody& world){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color pixelColor = Color::Black();
            for (int sample = 0; sample < samplesPerPixel; sample++) {
                Ray ray = getRay(x, y);
                pixelColor += calculateRayColor(ray, maxDepth, world);
            }
            drawPixel(x, y, pixelColor * pixelSampleScale);
        }
    }
}

void Render::destroy(){
    SDLRenderer::destroy();
}

Ray Render::getRay(int i, int j){
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    Point3D offset = random_sample_square();
    Point3D pixel_sample = this->viewport.getPixelPosOffset(i, j, offset.x, offset.y);
    
    auto ray_origin = this->cameraPos;
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}


Color Render::calculateRayColor(const Ray& ray, int depth, const GeoBody& world){
    if (depth <= 0)
        return Color::Black();
    HitRecord rec;

    if (world.hit(ray, Interval(0.001, infinity), rec)) {
        Vector3D direction = rec.normal + random_unit_vector(); // Lambertian sphere distribution
        // return 127.5 * (rec.normal + Point3D(1,1,1)); // 127.5 = 255/2
        return 0.5 * calculateRayColor(Ray(rec.p, direction), depth-1, world); // 127.5 = 255/2
    }
    return ray.getSkyboxColor();
}

