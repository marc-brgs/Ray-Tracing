#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"
#include "vector.hpp"

class Ray {
public:
    // Constructeur à partir des coordonnées
    Ray(float ox, float oy, float oz, float vx, float vy, float vz)
            : origin(ox, oy, oz), vector(vx, vy, vz) {}

    // Constructeur à partir du point d'origine et du vecteur directeur
    Ray(const Point& origin, const Vector& vector)
            : origin(origin), vector(vector) {}

    Point origin;
    Vector vector;
};

#endif // RAY_HPP