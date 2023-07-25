#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"
#include "vector.hpp"

class Ray {
public:
    Ray(float ox, float oy, float oz, float vx, float vy, float vz)
            : origin(ox, oy, oz), vector(vx, vy, vz) {}

    Ray(const Point& origin, const Vector& vector)
            : origin(origin), vector(vector) {}

    Ray normalized() {
        Vector v = vector / vector.norm();
        return Ray(origin, v);
    }

    Point origin;
    Vector vector;
};

#endif // RAY_HPP