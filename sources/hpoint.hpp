#ifndef HPOINT_HPP
#define HPOINT_HPP

class HPoint {
public:
    // Constructeur
    HPoint(float x, float y, float z, float w = 1.0) : x(x), y(y), z(z), w(w) {}

    // Accesseurs
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getW() const { return w; }

    // Produit scalaire
    float dot(const HPoint& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Opérateur d'addition
    HPoint operator+(const HPoint& other) const {
        return HPoint(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Opérateur de soustraction
    HPoint operator-(const HPoint& other) const {
        return HPoint(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Opérateur de multiplication par un réel
    HPoint operator*(float scalar) const {
        return HPoint(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // Opérateur de division par un réel
    HPoint operator/(float scalar) const {
        return HPoint(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    // Opérateur d'opposé
    HPoint operator-() const {
        return HPoint(-x, -y, -z, -w);
    }

private:
    float x, y, z, w;
};

#endif // HPOINT_HPP