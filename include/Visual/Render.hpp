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

using namespace std;


class Render: public SDLRenderer
{
private:
    Viewport viewport;
    Point3D cameraPos;
    Color calculateRayColor(const Ray& ray, const GeoBody& world);

public:
	//		Matrix full of zeros
	Render();
    bool init(int width, double aspectRatio);
    void destroy();
    void drawRays(const GeoBody& world);
};


#endif