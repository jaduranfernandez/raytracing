#include "../../include/Raytracing/GeoBodyList.hpp"

GeoBodyList::GeoBodyList() {
    // Constructor
}

GeoBodyList::~GeoBodyList() {
    // Destructor
    clear();
}


void GeoBodyList::clear() {
    objects.clear();
}

void GeoBodyList::add(shared_ptr<GeoBody> object) {
    objects.push_back(object);
}

bool GeoBodyList::hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_tmax;

    for (const auto& object : objects) {
        if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}