#ifndef COLOR_HPP
#define COLOR_HPP

#include <opencv2/core.hpp>

class Color {
public:
    float r, g, b;

    // Constructeur
    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    ~Color() {};

    Color mul(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    float operator[](int index) const {
        if (index == 0) return r;
        if (index == 1) return g;
        if (index == 2) return b;
        return 0.0f;
    }

    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }


    cv::Vec3b toVec3b() const {
        return cv::Vec3b(static_cast<uchar>(b * 255), static_cast<uchar>(g * 255), static_cast<uchar>(r * 255)); // vers BGR
    }

    Color& operator+=(const Color& other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    Color operator+(const Color& other) {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    void clamp() {
        r = std::max(0.0f, std::min(1.0f, r));
        g = std::max(0.0f, std::min(1.0f, g));
        b = std::max(0.0f, std::min(1.0f, b));
    }
};

#endif // COLOR_HPP