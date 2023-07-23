#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Entity.hpp"
#include "Ray.hpp"

class Camera : public Entity {
public:
    Camera(float focal) : focal(focal) {}

    // Méthode pour obtenir un rayon correspondant à un point de l'écran
    Ray getRay(float x, float y) const {
        float pixelX = x;
        float pixelY = y;

        Vector localVector(pixelX, pixelY, -focal);
        Vector globalVector = localToGlobal(localVector);
        Point globalOrigin = localToGlobal(Point(0, 0, 0));
        globalVector = globalVector.normalized();

        return Ray(globalOrigin, globalVector);
    }

private:
    float focal;
};

#endif // CAMERA_HPP