#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include "Color.hpp"
#include "../Math/Vector2D.hpp"
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

    int resolution;
    int window_width;
    int window_height;
    int gridX_step;
    int gridY_step;

public:
	//		Matrix full of zeros
	Render();
    bool setup(int width,int height);
    void destroy();
    void renderFrame();
    void drawSquare(Vector2D pos,int width, int height, Color color = Color::Grey());
    void drawPixel(Vector2D pos, Color color = Color::Grey());
    void drawGrid();
    void setupGrid(int xStep, int yStep);
};


#endif