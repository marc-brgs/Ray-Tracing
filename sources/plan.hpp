#ifndef PLAN_HPP
#define PLAN_HPP

#include "Object.hpp"
#include "Point.hpp"
#include "Material.hpp"

class Plan : public Object {
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

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);
        float z = 1;
        if (lo.z < 0)
            z = -1;
        return localToGlobal(Ray(lp, Vector(0, 0, z))).normalized();
    }

    Material getMaterial(const Point& p) const {
        Color ambient(0.0, 0.0, 0.0); // Composante ambiante (noir)
        Color diffuse(0, 0, 1); // Composante diffuse (bleu)
        Color specular(0.0, 0.0, 0.0); // Composante spéculaire (noir)
        float shininess = 0.0; // Exposant de brillance

        Material material(ambient, diffuse, specular, shininess);
        return material;
    }
};

#endif // PLAN_HPP