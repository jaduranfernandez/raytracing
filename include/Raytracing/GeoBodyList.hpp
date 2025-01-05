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
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

#endif // GeoBodyList_HPP
