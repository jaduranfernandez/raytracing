#ifndef RENDER_H
#define RENDER_H
#include "SDLRenderer.hpp"
#include "../Raytracing/GeoBody.hpp"
#include "Viewport.hpp"
#include <iostream>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <cstdint>
#include <omp.h>
#include <chrono>

using namespace std;


class Render: public SDLRenderer
{
private:
    Viewport viewport;
    Point3D cameraPos;
    int samplesPerPixel;   // Count of random samples for each pixel
    int maxDepth;
    double pixelSampleScale;
    Color calculateRayColor(const Ray& ray, int depth, const GeoBody& world);
    Ray getRay(int i, int j);
public:
	//		Matrix full of zeros
	Render();
    bool init(int width, double aspectRatio, int samplesPerPixel = 5, int maxDepth = 10);
    void destroy();
    void drawRays(const GeoBody& world);
};


#endif