#ifndef GeoBodyList_HPP
#define GeoBodyList_HPP

#include "GeoBody.hpp"
#include <vector>


class GeoBodyList: public GeoBody {
public:
    std::vector<shared_ptr<GeoBody>> objects;
    GeoBodyList();
    ~GeoBodyList();
    void clear();
    void add(shared_ptr<GeoBody> object);
    bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;
};

#endif // GeoBodyList_HPP
