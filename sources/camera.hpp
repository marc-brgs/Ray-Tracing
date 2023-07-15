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

        // Obtenir le vecteur de direction du rayon dans l'espace de la caméra
        Vector localVector(pixelX, pixelY, -focal);

        // Appliquer la rotation de la caméra au vecteur de direction
        Vector globalVector = localToGlobal(localVector);

        // Obtenir l'origine du rayon dans l'espace global en utilisant la transformation locale vers globale
        Point globalOrigin = localToGlobal(Point(0, 0, 0));

        // Normaliser le vecteur de direction
        globalVector = globalVector.normalized();

        // Créer et retourner le rayon correspondant
        return Ray(globalOrigin, globalVector);
    }

private:
    float focal;
};

#endif // CAMERA_HPP