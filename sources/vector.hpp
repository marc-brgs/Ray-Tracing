#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

class Vector {
public:
    float x, y, z;

    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector normalized() const {
        float magnitude = norm();
        return Vector(x / magnitude, y / magnitude, z / magnitude);
    }

    float dot(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector operator/(float scalar) const {
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    Vector operator-() const {
        return Vector(-x, -y, -z);
    }

    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        return 0.0f;
    }

    float& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else return z;
    }
};

#endif // VECTOR_HPP