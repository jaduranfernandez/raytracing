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
    color.a = 255;
    color.clamp();    
    if (x >= 0 && x < width && y >= 0 && y < height){
        color_buffer[(width * y) + x] = color.original;
    }
}

bool SDLRenderer::saveFrame(const char* filename){

    // Crear un framebuffer en el que renderizar la textura
    SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!target) {
        SDL_Log("Error creating target texture: %s", SDL_GetError());
        return false;
    }

    // Renderizar la textura en el framebuffer
    SDL_SetRenderTarget(renderer, target);
    SDL_RenderCopy(renderer, color_buffer_texture, nullptr, nullptr);

    // Crear una superficie desde el framebuffer
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);
    if (!surface) {
        SDL_Log("Error creating surface: %s", SDL_GetError());
        SDL_DestroyTexture(target);
        return false;
    }

    // Leer los píxeles del framebuffer a la superficie
    SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);

    // Guardar la superficie como imagen
    if (IMG_SavePNG(surface, filename) != 0) {
        SDL_Log("Error saving image: %s", IMG_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(target);
        return false;
    }

    // Limpiar
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(target);
    SDL_SetRenderTarget(renderer, nullptr);

    return true;
}
