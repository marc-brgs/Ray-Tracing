#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Object.hpp"
#include "Point.hpp"

class Cylinder: public Object {
public:
    bool intersect(const Ray& ray, Point& impact) const {
        Ray r = globalToLocal(ray).normalized();

        float a = r.vector.x * r.vector.x + r.vector.z * r.vector.z;
        float b = 2 * (r.vector.x * r.origin.x + r.vector.z * r.origin.z);
        float c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1.0;
        float delta = b * b - 4 * a * c;

        if (delta < 0)
            return false;

        float t;
        if (delta < 0.0001) {
            t = -b / (2 * a);
        } else {
            t = (-b - std::sqrt(delta)) / (2 * a);
            if (t < 0)
                t = (-b + std::sqrt(delta)) / (2 * a);
        }
        if (t < 0)
            return false;

        Point p = r.origin +  r.vector * t ;
        impact = localToGlobal(p);
        return true;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);
        Point temp=lo - Point(0, lo[1], 0);
        Vector normal = Vector(temp.x,temp.y,temp.z);
        if (normal.norm() > 1)
            return localToGlobal(Ray(lp, Vector(lp[0], 0, lp[2]))).normalized();

        return localToGlobal(Ray(lp, Vector(-lp[0], 0, -lp[2]))).normalized();
    }

    Material getMaterial(const Point& p) const {
        Color ambient(0.0, 0.0, 0.0); // Composante ambiante (noir)
        Color diffuse(0.5, 0.5, 0.0); // Composante diffuse (rouge)
        Color specular(0.0, 0.0, 0.0); // Composante spéculaire (noir)
        float shininess = 0.0; // Exposant de brillance

        Material material(ambient, diffuse, specular, shininess);
        return material;
    }
};


#endif //CYLINDER_HPP