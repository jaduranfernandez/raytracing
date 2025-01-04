#include "../../include/Visual/Render.hpp"


Render::Render(){
    this->color_buffer = NULL;
};

bool Render::setup(){
    this->cameraPos = Vector3D(0,0,0);
    this->viewport.setup(this->cameraPos, 1.0);
    int resolution = this->viewport.window_width*this->viewport.window_height;        
    this->color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * resolution);
    for (int i = 0; i < resolution; i++){
        this->color_buffer[i] = Color::Black().original;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initializing SDL\n");
        return false;
    }
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->viewport.window_width, this->viewport.window_height, 0);
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
    this->color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,this->viewport.window_width, this->viewport.window_height);

    return true;
};


void Render::destroy(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}


//      Draws collor buffer into screen
void Render::renderFrame(bool cleanAfterRender) {
    // Move bits from our 'color_buffer' variable to SDL color_buffer_texture
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(this->viewport.window_width * sizeof(uint32_t))
    );
    // Copy a portion of the 'color_buffer' texture to rendering target.
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

    if(cleanAfterRender){
        // Clear 'color_buffer'
        memset(color_buffer, 0xFFcc0000, viewport.window_width * viewport.window_height * sizeof(uint32_t));
    }

    // Swap the video buffer
    SDL_RenderPresent(renderer);

}

void Render::drawRays(){
    for (int y = 0; y < viewport.window_height; y++) {
        for (int x = 0; x < viewport.window_width; x++) {
            Point3D pixelCenter = this->viewport.getPixelPos(x, y);
            Vector3D rayDirection = pixelCenter - cameraPos;
            Ray r(cameraPos, rayDirection);
            Color pixelColor = r.getColor();
            drawPixel(x, y, pixelColor);
        }
    }
}


void Render::drawPixel(int x, int y, Color color){
    if (x >= 0 && x < this->viewport.window_width && y >= 0 && y < this->viewport.window_height){
        color_buffer[(this->viewport.window_width * y) + x] = color.original;
    }
}

