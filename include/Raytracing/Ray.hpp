#ifndef Ray_HPP
#define Ray_HPP

#include "../Math/Vector3D.hpp"
#include "../Visual/Color.hpp"

class Ray {
public:
    Ray();
    ~Ray();
    Ray(const Point3D& origin, const Vector3D& direction);

    const Point3D& origin() const  { return orig; }
    const Vector3D& direction() const { return dir; }

    Point3D at(double t) const;
    Color getSkyboxColor();
private:
    Point3D orig;
    Vector3D dir;
    double hitSphere(const Point3D& center, double radius);
};

#endif // Ray_HPP
