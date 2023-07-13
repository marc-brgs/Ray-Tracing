#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"

class Material {
public:
    Color ka;  // Composante ambiante
    Color kd;  // Composante diffuse
    Color ks;  // Composante spéculaire
    float shininess;  // Exposant de brillance

    // Constructeur
    Material(const Color& ka, const Color& kd, const Color& ks, float shininess)
            : ka(ka), kd(kd), ks(ks), shininess(shininess) {}
};

#endif // MATERIAL_HPP
