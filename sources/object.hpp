#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Entity.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Object : public Entity {
public:
    bool hasTexture;
    cv::Mat texture;
    float shininess;
    Color specular;

    Object() : hasTexture(false), shininess(0.5), specular(Color(0.1f, 0.1f, 0.1f)) {}
    virtual Material getMaterial(const Point& p) const = 0;
    virtual Ray getNormal(const Point& p, const Point& o) const = 0;
    virtual bool intersect(const Ray& ray, Point& impact) const = 0;

    void loadTexture(const std::string& imagePath) {
        texture = cv::imread(imagePath);

        if (texture.empty()) {
            std::cout << "Erreur lors du chargement de l'image de texture : " << imagePath << std::endl;
        }

        hasTexture = true;
    }
};

#endif // OBJECT_HPP