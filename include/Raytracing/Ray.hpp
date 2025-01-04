#ifndef Ray_HPP
#define Ray_HPP

#include "../Math/Vector3D.hpp"

class Ray {
public:
    Ray();
    ~Ray();
    Ray(const Point3D& origin, const Vector3D& direction);

    const Point3D& origin() const  { return orig; }
    const Vector3D& direction() const { return dir; }

    Point3D at(double t) const;

private:
    Point3D orig;
    Vector3D dir;
};

#endif // Ray_HPP
