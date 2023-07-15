#ifndef CUBE_HPP
#define CUBE_HPP

#include "Entity.hpp"
#include "Object.hpp"
#include "Vector.hpp"
#include "Point.hpp"

class Cube : public Object {
public:
    Cube() {}

    float interSide(const Ray& r, int dim, float offset) const {
        float t = -1;
        if (r.vector[dim] < 0.00001 && r.vector[dim] > -0.00001)
            return -1;
        t = (offset - r.origin[dim]) / r.vector[dim];
        if (t < 0)
            return -1;
        for (int d = 0; d < 3; d++) {
            if (d == dim)
                continue;
            float x = r.origin[d] + t * r.vector[d];
            if (x < -1 || x > 1)
                return -1;
        }
        return t;
    }

    bool intersect(const Ray& ray, Point& impact) const {
        Ray r = globalToLocal(ray).normalized();

        float mint = -1;
        float offsets[] = { -1, 1 };
        for (int d = 0; d < 3; d++) {
            for (int o = 0; o < 2; o++) {
                float t = interSide(r, d, offsets[o]);
                if (t >= 0 && (mint < 0 || mint > t)) {
                    mint = t;
                }
            }
        }

        if (mint >= 0) {
            impact = localToGlobal(r.origin + r.vector * mint);
            return true;
        }

        return false;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);
        Vector v(0, 0, 0);

        if (lp[0] > 0.999)
            v[0] = 1.0;
        else if (lp[0] < -0.999)
            v[0] = -1.0;
        else if (lp[1] > 0.999)
            v[1] = 1.0;
        else if (lp[1] < -0.999)
            v[1] = -1.0;
        else if (lp[2] > 0.999)
            v[2] = 1.0;
        else if (lp[2] < -0.999)
            v[2] = -1.0;

        if (lo[0] < 1 && lo[0] > -1 && lo[1] < 1 && lo[1] > -1 && lo[2] < 1 && lo[2] > -1)
            return localToGlobal(Ray(lp, v)).normalized();
        return localToGlobal(Ray(lp, v)).normalized();
    }

    Material getMaterial(const Point& p) const {
        Color ambient(0.0, 0.0, 0.0); // Composante ambiante (noir)
        Color diffuse(0.0, 1, 0); // Composante diffuse (rouge)
        Color specular(0.0, 0.0, 0.0); // Composante spéculaire (noir)
        float shininess = 0; // Exposant de brillance

        Material material(ambient, diffuse, specular, shininess);
        return material;
    }
};

#endif // CUBE_HPP