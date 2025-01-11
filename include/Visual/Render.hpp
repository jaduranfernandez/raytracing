#ifndef RENDER_H
#define RENDER_H
#include "SDLRenderer.hpp"
#include "../Raytracing/GeoBody.hpp"
#include "../Raytracing/Material.hpp"
#include "Viewport.hpp"
#include <iostream>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <cstdint>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;


class Render: public SDLRenderer
{
private:
    Viewport viewport;
    Camera cam;
    int samplesPerPixel;   // Count of random samples for each pixel
    int maxDepth;
    double pixelSampleScale;
    Color calculateRayColor(const Ray& ray, int depth, const GeoBody& world);
    Ray getRay(int i, int j);
    void renderSection(int startY, int endY,const GeoBody& world);
    Point3D defocusDiskSample() const;
public:
	//		Matrix full of zeros
	Render();
	Render(Camera cam);
    bool init(int width, double aspectRatio, int samplesPerPixel = 5, int maxDepth = 10);
    void destroy();
    void drawRays(const GeoBody& world);
};


#endif