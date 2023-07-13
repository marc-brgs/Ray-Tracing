#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Plan.hpp"

class Square : public Plan {
public:
    Square() {}

    bool intersect(const Ray& ray, Point& impact) const {
        Ray local_ray = globalToLocal(ray);
        float t = -local_ray.origin.getZ() / local_ray.vector.getZ();
        Point local_intersection = local_ray.origin + local_ray.vector * t;

        if (std::abs(local_intersection.getX()) <= 1.0 && std::abs(local_intersection.getY()) <= 1.0) {
            impact = localToGlobal(local_intersection);
            return true;
        }

        return false;
    }
};

#endif // SQUARE_HPP