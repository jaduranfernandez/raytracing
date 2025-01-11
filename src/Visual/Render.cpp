#include "../../include/Visual/Render.hpp"


Render::Render(){
    cam = Camera();
    cam.vFov = 20;
    cam.position = Point3D(10,2,0);
    cam.lookfrom = cam.position;
    cam.lookat   = Point3D(-3,0,0);
    cam.vup      = Vector3D(0,1,0);
    cam.focal_length = (cam.lookfrom - cam.lookat).length();
};

Render::Render(Camera cam){
    this->cam = cam;
    if(cam.focal_length == 0)
        this->cam.focal_length = (cam.lookfrom - cam.lookat).length();
}

bool Render::init(int width, double aspectRatio, int samples, int maxDepth){
    this->samplesPerPixel = samples;
    this->maxDepth = maxDepth;
    this->viewport.setup(this->cam, aspectRatio, width, height);
    pixelSampleScale = 1.0 / samplesPerPixel;
    return SDLRenderer::init(width, height);
};


void Render::drawRays(const GeoBody& world){
    auto start = std::chrono::high_resolution_clock::now();
    int numThreads = std::thread::hardware_concurrency();
    int rowsPerThread = height / numThreads;

    std::vector<std::thread> threads;

    for (int t = 0; t < numThreads; ++t) {
        int startY = t * rowsPerThread;
        int endY = (t == numThreads - 1) ? height : (t + 1) * rowsPerThread;

        threads.emplace_back([this, startY, endY, &world]() {
            this->renderSection(startY, endY, world);
        });
        // threads.emplace_back(renderSection, startY, endY, std::ref(world));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;
}


void Render::renderSection(int startY, int endY,const GeoBody& world){
    for (int y = startY; y < endY; y++) {
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
    
    // auto ray_origin = this->cam.position;
    auto ray_origin = (this->cam.defocus_angle <= 0) ? this->cam.position : defocusDiskSample();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}


Color Render::calculateRayColor(const Ray& ray, int depth, const GeoBody& world){
    if (depth <= 0)
        return Color::Black();
    HitRecord rec;

    if (world.hit(ray, Interval(0.001, infinity), rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat->scatter(ray, rec, attenuation, scattered)){            
            return attenuation * calculateRayColor(scattered, depth-1, world);
        }
        return Color::Black();
        // Vector3D direction = rec.normal + random_unit_vector(); // Lambertian sphere distribution
        // return 127.5 * (rec.normal + Point3D(1,1,1)); // 127.5 = 255/2
        // return 0.5 * calculateRayColor(Ray(rec.p, direction), depth-1, world); // 127.5 = 255/2
    }
    return ray.getSkyboxColor();
}



Point3D Render::defocusDiskSample() const{
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return this->cam.position + (p[0] * viewport.defocus_disk_u) + (p[1] * viewport.defocus_disk_v);
}

