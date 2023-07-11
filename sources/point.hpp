#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
    float x, y, z;

    // Constructeur
    Point(float x, float y, float z) : x(x), y(y), z(z) {}

    // Accesseurs
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    // Produit scalaire
    float dot(const Point& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Opérateur d'addition
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    // Opérateur de soustraction
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y, z - other.z);
    }

    // Opérateur de multiplication par un réel
    Point operator*(float scalar) const {
        return Point(x * scalar, y * scalar, z * scalar);
    }

    // Opérateur de division par un réel
    Point operator/(float scalar) const {
        return Point(x / scalar, y / scalar, z / scalar);
    }

    // Opérateur d'opposé
    Point operator-() const {
        return Point(-x, -y, -z);
    }
};

#endif // POINT_HPP