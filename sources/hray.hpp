#ifndef HRAY_HPP
#define HRAY_HPP

#include "HPoint.hpp"
#include "HVector.hpp"

class HRay {
public:
    // Constructeur à partir des coordonnées
    HRay(float ox, float oy, float oz, float vx, float vy, float vz)
            : origin(ox, oy, oz, 1.0), vector(vx, vy, vz, 0.0) {}

    // Constructeur à partir du point d'origine et du vecteur directeur
    HRay(const HPoint& origin, const HVector& vector)
            : origin(origin), vector(vector) {}

    HPoint origin;
    HVector vector;
};

#endif // HRAY_HPP