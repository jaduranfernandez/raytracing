#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "../include/module_1/test.hpp"


int main(int argc, char *argv[])
{
    testFunction();
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									1000, 1000, 0);

    bool close = false;
	// animation loop
	while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				close = true;
				break;
		    }
            // calculates to 60 fps
            SDL_Delay(1000 / 60);
	    }
    }

	// destroy window
	SDL_DestroyWindow(win);
	
	// close SDL
	SDL_Quit();

	return 0;
}
