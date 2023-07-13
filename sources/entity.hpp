#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Matrix.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

class Entity {
public:
    Entity() : transformationMatrix(Matrix()) {}

    void translate(float x, float y, float z) {
        Matrix translationMatrix;
        translationMatrix(0, 3) = x;
        translationMatrix(1, 3) = y;
        translationMatrix(2, 3) = z;
        transformationMatrix = translationMatrix * transformationMatrix;
    }

    void rotateX(float deg) {
        float rad = degToRad(deg);
        Matrix rotationMatrix;
        rotationMatrix(1, 1) = cos(rad);
        rotationMatrix(1, 2) = -sin(rad);
        rotationMatrix(2, 1) = sin(rad);
        rotationMatrix(2, 2) = cos(rad);
        transformationMatrix = rotationMatrix * transformationMatrix;
    }

    void rotateY(float deg) {
        float rad = degToRad(deg);
        Matrix rotationMatrix;
        rotationMatrix(0, 0) = cos(rad);
        rotationMatrix(0, 2) = sin(rad);
        rotationMatrix(2, 0) = -sin(rad);
        rotationMatrix(2, 2) = cos(rad);
        transformationMatrix = rotationMatrix * transformationMatrix;
    }

    void rotateZ(float deg) {
        float rad = degToRad(deg);
        Matrix rotationMatrix;
        rotationMatrix(0, 0) = cos(rad);
        rotationMatrix(0, 1) = -sin(rad);
        rotationMatrix(1, 0) = sin(rad);
        rotationMatrix(1, 1) = cos(rad);
        transformationMatrix = rotationMatrix * transformationMatrix;
    }

    void scale(float factor) {
        Matrix scalingMatrix;
        scalingMatrix(0, 0) = factor;
        scalingMatrix(1, 1) = factor;
        scalingMatrix(2, 2) = factor;
        transformationMatrix = scalingMatrix * transformationMatrix;
    }

    Point localToGlobal(const Point& point) const {
        HPoint hPoint(point.getX(), point.getY(), point.getZ(), 1.0);
        HPoint transformedPoint = transformationMatrix * hPoint;
        return Point(transformedPoint.getX(), transformedPoint.getY(), transformedPoint.getZ());
    }

    Vector localToGlobal(const Vector& vector) const {
        HVector hVector(vector.getX(), vector.getY(), vector.getZ(), 0.0);
        HVector transformedVector = transformationMatrix * hVector;
        return Vector(transformedVector.getX(), transformedVector.getY(), transformedVector.getZ());
    }

    Point globalToLocal(const Point& point) const {
        Matrix inverseMatrix = transformationMatrix.inverse();
        HPoint hPoint(point.getX(), point.getY(), point.getZ(), 1.0);
        HPoint transformedPoint = inverseMatrix * hPoint;
        return Point(transformedPoint.getX(), transformedPoint.getY(), transformedPoint.getZ());
    }

    Vector globalToLocal(const Vector& vector) const {
        Matrix inverseMatrix = transformationMatrix.inverse();
        HVector hVector(vector.getX(), vector.getY(), vector.getZ(), 0.0);
        HVector transformedVector = inverseMatrix * hVector;
        return Vector(transformedVector.getX(), transformedVector.getY(), transformedVector.getZ());
    }

    Ray localToGlobal(const Ray& ray) const {
        Point globalOrigin = localToGlobal(ray.origin);
        Vector globalDirection = localToGlobal(ray.vector);
        return Ray(globalOrigin, globalDirection);
    }

    Ray globalToLocal(const Ray& ray) const {
        Point localOrigin = globalToLocal(ray.origin);
        Vector localDirection = globalToLocal(ray.vector);
        return Ray(localOrigin, localDirection);
    }

private:
    Matrix transformationMatrix;

    float degToRad(float deg) {
        return deg * M_PI / 180.0;
    }
};

#endif // ENTITY_HPP