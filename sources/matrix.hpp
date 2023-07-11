#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include "HPoint.hpp"
#include "HVector.hpp"

class Matrix {
public:
    // Constructeur par défaut pour une matrice identité
    Matrix() {
        values.fill(0.0);
        values[0] = values[5] = values[10] = values[15] = 1.0;
    }

    // Accès à une case spécifique de la matrice
    float& operator()(int row, int col) {
        return values[row * 4 + col];
    }

    // Accès en lecture seule à une case spécifique de la matrice
    float operator()(int row, int col) const {
        return values[row * 4 + col];
    }

    // Calcul de l'inverse de la matrice
    Matrix inverse() const {
        // Implémentation de l'inversion de la matrice
        // ...
        // Remplacez cette implémentation par votre propre code pour l'inversion de la matrice
        return Matrix();
    }

    // Multiplication de matrices
    Matrix operator*(const Matrix& other) const {
        Matrix result;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                float sum = 0.0;
                for (int k = 0; k < 4; ++k) {
                    sum += values[i * 4 + k] * other(k, j);
                }
                result(i, j) = sum;
            }
        }

        return result;
    }

    // Multiplication d'une matrice avec un HPoint
    HPoint operator*(const HPoint& point) const {
        float x = values[0] * point.getX() + values[1] * point.getY() + values[2] * point.getZ() + values[3] * point.getW();
        float y = values[4] * point.getX() + values[5] * point.getY() + values[6] * point.getZ() + values[7] * point.getW();
        float z = values[8] * point.getX() + values[9] * point.getY() + values[10] * point.getZ() + values[11] * point.getW();
        float w = values[12] * point.getX() + values[13] * point.getY() + values[14] * point.getZ() + values[15] * point.getW();

        return HPoint(x, y, z, w);
    }

    // Multiplication d'une matrice avec un HVector
    HVector operator*(const HVector& vector) const {
        float x = values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ() + values[3] * vector.getW();
        float y = values[4] * vector.getX() + values[5] * vector.getY() + values[6] * vector.getZ() + values[7] * vector.getW();
        float z = values[8] * vector.getX() + values[9] * vector.getY() + values[10] * vector.getZ() + values[11] * vector.getW();
        float w = values[12] * vector.getX() + values[13] * vector.getY() + values[14] * vector.getZ() + values[15] * vector.getW();

        return HVector(x, y, z, w);
    }

private:
    std::array<float, 16> values;
};

#endif // MATRIX_HPP