#include "../../include/Visual/SDLRenderer.hpp"

SDLRenderer::SDLRenderer() {
    // Constructor
    this->color_buffer = NULL;
}

SDLRenderer::~SDLRenderer() {
    // Destructor
}

bool SDLRenderer::init(int width, int height){
    this->width = width;
    this->height = height;
    int resolution = width*height;        
    this->color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * resolution);
    for (int i = 0; i < resolution; i++){
        this->color_buffer[i] = Color::Black().original;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initializing SDL\n");
        return false;
    }
    window = SDL_CreateWindow("Scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(!this->window){
        fprintf(stderr, "Error creating SDL window\n");
        return false;
    }
    //  Arguments:
    //  (window, -1 -> first driver available, 0 -> no flag)
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if(!this->renderer){
        fprintf(stderr, "Error creating SDL renderer \n");
        return false;
    }
    this->color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,width, height);
    return true;
}

void SDLRenderer::destroy(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SDLRenderer::renderFrame(bool cleanAfterRender){
    // Move bits from our 'color_buffer' variable to SDL color_buffer_texture
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(width * sizeof(uint32_t))
    );
    // Copy a portion of the 'color_buffer' texture to rendering target.
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

    if(cleanAfterRender){
        // Clear 'color_buffer'
        memset(color_buffer, 0xFFcc0000, width * height * sizeof(uint32_t));
    }

    // Swap the video buffer
    SDL_RenderPresent(renderer);
}

void SDLRenderer::drawPixel(int x, int y, Color color){
    if (x >= 0 && x < width && y >= 0 && y < height){
        color_buffer[(width * y) + x] = color.original;
    }
}

bool SDLRenderer::saveRender(std::string path){


    return false;
}
