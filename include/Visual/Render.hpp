#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include "Color.hpp"
#include "../Math/Vector2D.hpp"
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
    Viewport viewport;
    uint32_t* color_buffer;

    int gridX_step;
    int gridY_step;

public:
	//		Matrix full of zeros
	Render();
    bool setup();
    void destroy();
    void renderFrame();
    void drawSquare(Vector2D pos,int width, int height, Color color = Color::Grey());
    void drawPixel(Vector2D pos, Color color = Color::Grey());
    void drawGrid();
    void setupGrid(int xStep, int yStep);
};


#endif