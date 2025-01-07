#ifndef Material_HPP
#define Material_HPP

#include "GeoBody.hpp"

class Material {
public:
    ~Material() = default;
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const;
};

class Lambertian : public Material {
  public:
    Lambertian(const Color& albedo) : albedo(albedo) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

  private:
    Color albedo;
};

class Metal : public Material {
  public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

  private:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material {
  public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

  private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;

    static double reflectance(double cosine, double refraction_index);
};


#endif // Material_HPP
