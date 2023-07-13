#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Entity.hpp"
#include "Object.hpp"
#include "Vector.hpp"

class Sphere : public Object {
public:
    Sphere() {}

    bool intersect(const Ray& ray, Point& impact) const {
        Ray local_ray = globalToLocal(ray);

        float a = local_ray.vector.dot(local_ray.vector);
        float b = 2 * local_ray.vector.dot(Vector(local_ray.origin.x, local_ray.origin.y, local_ray.origin.z));
        float c = local_ray.origin.dot(local_ray.origin) - 1.0;
        float delta = b * b - 4 * a * c;

        if (delta < 0) {
            return false;
        }

        float t1 = (-b - sqrt(delta)) / (2 * a);
        float t2 = (-b + sqrt(delta)) / (2 * a);

        float t = t1 < t2 ? t1 : t2; // min
        if (t > 0) {
            Point local_intersection = local_ray.origin + (local_ray.vector * t);
            impact = localToGlobal(local_intersection);
            return true;
        }

        t = t1 > t2 ? t1 : t2; // max
        if (t > 0) {
            Point local_intersection = local_ray.origin + (local_ray.vector * t);
            impact = localToGlobal(local_intersection);
            return true;
        }

        return false;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);

        Vector normal = Vector(lp.x, lp.y, lp.z).normalized();

        if (Vector(lo.x, lo.y, lo.z).norm() < 1) {
            normal = -normal;
        }

        return localToGlobal(Ray(lp, normal)).normalized();
    }

    Material getMaterial(const Point& p) const {
        Color ambient(0.0, 0.0, 0.0); // Composante ambiante (noir)
        Color diffuse(1.0, 0.0, 0.0); // Composante diffuse (rouge)
        Color specular(0.0, 0.0, 0.0); // Composante spéculaire (noir)
        float shininess = 0.0; // Exposant de brillance

        Material material(ambient, diffuse, specular, shininess);
        return material;
    }
};

#endif // SPHERE_HPP