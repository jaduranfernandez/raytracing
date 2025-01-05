#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include "Color.hpp"
#include "../Raytracing/GeoBody.hpp"
#include "Viewport.hpp"
#include <iostream>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <cstdint>

using namespace std;


class Render
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture * color_buffer_texture;
    uint32_t* color_buffer; 
    Viewport viewport;
    Point3D cameraPos;

public:
	//		Matrix full of zeros
	Render();
    bool setup();
    void destroy();
    void renderFrame(bool cleanAfterRender = true);
    void drawRays(const GeoBody& world);
    void drawPixel(int x, int y, Color color = Color::Grey());
};


#endif