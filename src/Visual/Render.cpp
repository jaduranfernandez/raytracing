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
            
            Color pixelColor;
            HitRecord rec;
            if (world.hit(r, 0, infinity, rec)) {
                pixelColor = 127.5 * (rec.normal + Point3D(1,1,1)); // 127.5 = 255/2
            }
            else{
                pixelColor = r.getSkyboxColor();
            }

            drawPixel(x, y, pixelColor);
        }
    }
}

void Render::destroy(){
    SDLRenderer::destroy();
}
