#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Entity.hpp"
#include "Ray.hpp"

class Camera : public Entity {
public:
    Camera(float focal) : focal(focal) {}

    // Méthode pour obtenir un rayon correspondant à un point de l'écran
    Ray getRay(float x, float y) const {
        Point  globalOrigin = localToGlobal(Point(0, 0, 0));
        Vector globalVector = Vector(x * 2 - 1, y * 2 - 1, -focal).normalized();
        return Ray(globalOrigin, globalVector);
    }

private:
    float focal;
};

#endif // CAMERA_HPP


