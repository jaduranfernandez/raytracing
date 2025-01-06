#include "../../include/Raytracing/Material.hpp"

bool Material::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const{
    (void)r_in;
    (void)rec;
    (void)attenuation;
    (void)scattered;
    return false;
}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    (void)r_in;
    Vector3D scatter_direction = rec.normal + random_unit_vector();
    // Catch degenerate scatter direction
    if (scatter_direction.nearZero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    Vector3D reflected = reflect(r_in.direction(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return true;
}
