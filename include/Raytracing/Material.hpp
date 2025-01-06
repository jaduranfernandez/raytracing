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
    Metal(const Color& albedo) : albedo(albedo) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

  private:
    Color albedo;
};


#endif // Material_HPP
