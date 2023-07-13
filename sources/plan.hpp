#ifndef PLAN_HPP
#define PLAN_HPP

#include "Entity.hpp"

class Plan : public Entity {
public:
    Plan() {}

    bool intersect(const Ray& ray, Point& impact) const {
        Ray local_ray = globalToLocal(ray);
        float t = -local_ray.origin.getZ() / local_ray.vector.getZ();
        Point local_intersection = local_ray.origin + local_ray.vector * t;

        if (t >= 0) {
            impact = localToGlobal(local_intersection);
            return true;
        }

        return false;
    }
};

#endif // PLAN_HPP