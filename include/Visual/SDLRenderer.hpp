#ifndef SDLRenderer_HPP
#define SDLRenderer_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Color.hpp"
#include <iostream>
#include <string>

class SDLRenderer {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture * color_buffer_texture;
    uint32_t* color_buffer; 

protected:
    int width;
    int height;
    bool init(int width, int height);
    void drawPixel(int x, int y, Color color = Color::Grey());
    virtual void destroy();

public:
    SDLRenderer();
    ~SDLRenderer();
    void renderFrame(bool cleanAfterRender = true);
    bool saveFrame(const char* filename);
};

#endif // SDLRenderer_HPP
