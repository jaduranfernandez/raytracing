#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
// #include "../include/Visual/Render.hpp"
// #include "../include/Math/Vector3D.hpp"
// #include "../include/Math/Utils.hpp"
// #include "../include/Raytracing/GeoBodyList.hpp"
// #include "../include/Raytracing/Sphere.hpp"
#include <iostream>

#include "../include/Math/Utils.hpp"
// #include "../include/Raytracing/GeoBody.hpp"
#include "../include/Raytracing/GeoBodyList.hpp"
#include "../include/Raytracing/Sphere.hpp"
#include "../include/Visual/Render.hpp"


using std::make_shared;
using std::shared_ptr;

int main()
{
	GeoBodyList world;
    world.add(make_shared<Sphere>(Point3D(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point3D(0,-100.5,-1), 100));

	Render render = Render();
	bool close = !render.init(800, 16.0/9.0);
	render.drawRays(world);
	render.renderFrame(true);
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
	render.destroy();
	return 0;
}
