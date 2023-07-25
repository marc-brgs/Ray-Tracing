#ifndef POINT_HPP
#define POINT_HPP

#include "Vector.hpp"

class Point {
public:
    float x, y, z;

    Point() {}
    Point(float x, float y, float z) : x(x), y(y), z(z) {}

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    float dot(const Point& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y, z - other.z);
    }

    Point operator*(float scalar) const {
        return Point(x * scalar, y * scalar, z * scalar);
    }

    Point operator/(float scalar) const {
        return Point(x / scalar, y / scalar, z / scalar);
    }

    Point operator-() const {
        return Point(-x, -y, -z);
    }

    Point operator+(const Vector& vector) const {
        return Point(x + vector.getX(), y + vector.getY(), z + vector.getZ());
    }

    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        return 0.0f;
    }
};

#endif // POINT_HPP