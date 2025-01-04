#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "../include/Visual/Render.hpp"
#include "../include/Math/Vector3D.hpp"
#include <iostream>

int main()
{
	Render render = Render();
	bool close = !render.setup();
	while (!close) {
		SDL_Event event;
		// Events management
		while (SDL_PollEvent(&event)) {
			render.drawSquare(Vector2D(0, 0), 100, 100);
			render.renderFrame();
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
	render.destroy();
	return 0;
}
