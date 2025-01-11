#include <SDL2/SDL_timer.h>
#include <iostream>
#include "../include/Math/Utils.hpp"
#include "../include/Raytracing/GeoBodyList.hpp"
#include "../include/Raytracing/Material.hpp"
#include "../include/Raytracing/Sphere.hpp"
#include "../include/Visual/Render.hpp"


using std::make_shared;
using std::shared_ptr;

shared_ptr<Sphere> randomSphere(Point3D center);

bool isInsideSphere(Sphere origin, Point3D newSpherePos, double newSphereRadius);

int main(int argc, const char * argv[])
{
    std::srand(24041999);
	// Scene
	GeoBodyList world;

    auto ground_material = make_shared<Lambertian>(Color(131, 181, 197));
    world.add(make_shared<Sphere>(Point3D(0,-1000,0), 1000, ground_material));

    auto material_outer_bubble = make_shared<Dielectric>(1.5);
	auto material_inner_bubble = make_shared<Dielectric>(1.00 / 1.50);
    Point3D bubblePosition = Point3D(4, 0.4, 0);
    world.add(make_shared<Sphere>(bubblePosition, 0.4, material_outer_bubble));
    world.add(make_shared<Sphere>(bubblePosition, 0.3, material_inner_bubble));

    auto material1 = make_shared<Metal>(Color(204, 140, 100), 0.2);
    world.add(make_shared<Sphere>(Point3D(0, 1, -1.5), 1.0, material1));

    auto material2 = make_shared<Metal>(Color::White(), 0.0);
    world.add(make_shared<Sphere>(Point3D(0, 1, 1.5), 1.0, material2));

    int spheresGridSize = 16;

    for (int a = -spheresGridSize/2; a < spheresGridSize/2; a++) {
        for (int b = -spheresGridSize/2; b < spheresGridSize/2; b++) {
            Point3D center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if ((center - Point3D(4, 0.2, 0)).length() > 0.9) {
                world.add(randomSphere(center));
            }
        }
    }

    // Camera
    Camera cam = Camera();
    cam.vFov = 20;
    cam.position = Point3D(10,2,0);
    cam.lookfrom = cam.position;
    cam.lookat   = Point3D(-3,0,0);
    cam.vup      = Vector3D(0,1,0);
    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

	// Render
	int width = 1200;
	double aspectRatio = 16.0/9.0;
	int samplesPerPixel = 500;
	int maxDepth = 50;

	Render render = Render(cam);
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


shared_ptr<Sphere> randomSphere(Point3D center){
    auto choose_mat = random_double();
    shared_ptr<Material> sphere_material;
    if (choose_mat < 0.8) {
        // diffuse
        Vector3D albedo = Vector3D::random(0, 255);
        Color albedoColor = Color(albedo);
        albedoColor.clamp();
        sphere_material = make_shared<Lambertian>(albedoColor);
        return (make_shared<Sphere>(center, 0.2, sphere_material));
    } else if (choose_mat < 0.95) {
        // metal
        Color albedo = Color(Vector3D::random(127, 255));
        auto fuzz = random_double(0, 0.5);
        sphere_material = make_shared<Metal>(albedo, fuzz);
        return (make_shared<Sphere>(center, 0.2, sphere_material));
    } else {
        // glass
        sphere_material = make_shared<Dielectric>(1.5);
        return (make_shared<Sphere>(center, 0.2, sphere_material));
    }
}


bool isInsideSphere(Sphere origin, Point3D newSpherePos, double newSphereRadius){
    return (newSpherePos - Point3D(4, 0.2, 0)).length() < (newSphereRadius + origin.getRadius());
}
