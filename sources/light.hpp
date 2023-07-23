#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"
#include "Ray.hpp"
#include "Vector.hpp"
#include "Color.hpp"

class Light : public Entity {
public:
    Color id; // Composante diffuse de la lumière
    Color is; // Composante spéculaire de la lumière

    Light(const Color& diffuse, const Color& specular) : id(diffuse), is(specular) {}
    Light() : id(Color()), is(Color()) {}

    Ray getRayFromLight(const Point& p) const {
        Point globalOrigin = localToGlobal(Point(0, 0, 0));
        Vector direction = Vector(p.x - globalOrigin.x, p.y - globalOrigin.y, p.z - globalOrigin.z);
        return Ray(p, direction.normalized());
    }

    Ray getRayToLight(const Point& p) const {
        Point globalOrigin = localToGlobal(Point(0, 0, 0));
        Vector direction = Vector(globalOrigin.x - p.x, globalOrigin.y - p.y, globalOrigin.z - p.z);
        return Ray(p, direction.normalized());
    }

    Vector getVectorFromLight(const Point& p) const {
        Point globalOrigin = localToGlobal(Point(0, 0, 0));
        return (Vector(p.x - globalOrigin.x, p.y - globalOrigin.y, p.z - globalOrigin.z)).normalized();
    }

    Vector getVectorToLight(const Point& p) const {
        Point globalOrigin = localToGlobal(Point(0, 0, 0));
        return (Vector(globalOrigin.x - p.x, globalOrigin.y - p.y, globalOrigin.z - p.z)).normalized();
    }
};

#endif // LIGHT_HPP