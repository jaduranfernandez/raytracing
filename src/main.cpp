#include <SDL2/SDL_timer.h>
#include <iostream>

#include "../include/Math/Utils.hpp"
// #include "../include/Raytracing/GeoBody.hpp"
#include "../include/Raytracing/GeoBodyList.hpp"
#include "../include/Raytracing/Material.hpp"
#include "../include/Raytracing/Sphere.hpp"
#include "../include/Visual/Render.hpp"


using std::make_shared;
using std::shared_ptr;

int main(int argc, const char * argv[])
{

	// Scene
	GeoBodyList world;

	auto material_ground = make_shared<Lambertian>(Color(204, 204, 0));
    auto material_center = make_shared<Lambertian>(Color(50, 100, 127));
    auto material_left   = make_shared<Metal>(Color(204, 204, 204));
    auto material_right  = make_shared<Metal>(Color(204, 140, 100));

	world.add(make_shared<Sphere>(Point3D( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3D( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(Point3D(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(Point3D( 1.0,    0.0, -1.0),   0.5, material_right));

    // world.add(make_shared<Sphere>(Point3D(0,0,-1), 0.5));
    // world.add(make_shared<Sphere>(Point3D(0,-100.5,-1), 100));

	// Render
	int width = 800;
	double aspectRatio = 16.0/9.0;
	int samplesPerPixel = 25;
	int maxDepth = 50;

	Render render = Render();
	bool close = !render.init(width, aspectRatio, samplesPerPixel, maxDepth);
	render.drawRays(world);
	render.renderFrame(true);
	
	if(argc > 1){
		std::string filename = createFilePath("screenshots/", argv[1]);
		render.saveFrame(filename.c_str());
	}
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
