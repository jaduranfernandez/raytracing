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
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    attenuation = Color::White();
    double ri = rec.isFrontFace ? (1.0/refraction_index) : refraction_index;

    Vector3D unit_direction = unit_vector(r_in.direction());
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vector3D direction;

    if (cannot_refract)
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);

    scattered = Ray(rec.p, direction);
    return true;
}
