#ifndef HVECTOR_HPP
#define HVECTOR_HPP

#include <cmath>

class HVector {
private:
    float x, y, z, w;

public:
    // Constructeur
    HVector(float x, float y, float z, float w = 1.0) : x(x), y(y), z(z), w(w) {}

    // Accesseurs
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getW() const { return w; }

    // Norme du vecteur
    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Vecteur normalisé
    HVector normalized() const {
        float magnitude = norm();
        return HVector(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
    }

    // Produit scalaire
    float dot(const HVector& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Opérateur d'addition
    HVector operator+(const HVector& other) const {
        return HVector(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Opérateur de soustraction
    HVector operator-(const HVector& other) const {
        return HVector(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Opérateur de multiplication par un réel
    HVector operator*(float scalar) const {
        return HVector(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // Opérateur de division par un réel
    HVector operator/(float scalar) const {
        return HVector(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    // Opérateur d'opposé
    HVector operator-() const {
        return HVector(-x, -y, -z, -w);
    }
};

#endif // HVECTOR_HPP