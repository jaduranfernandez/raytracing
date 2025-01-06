#include "../../include/Raytracing/Material.hpp"

Material::~Material() {
    // Destructor
}

bool Material::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const{
    return false;
}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    Vector3D scatter_direction = rec.normal + random_unit_vector();
    // Catch degenerate scatter direction
    if (scatter_direction.nearZero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

