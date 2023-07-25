#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"

class Scene {
private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Color background;
    Color ambient;

public:
    Scene(const Color& background, const Color& ambient)
            : background(background), ambient(ambient) {}

    ~Scene() {
        for (Object* obj : objects) {
            delete obj;
        }
        for (Light* light : lights) {
            delete light;
        }
    }

    // Opérateur par affectation
    Scene& operator=(const Scene& other) {
        if (this == &other) {
            return *this;
        }

        background = other.background;
        ambient = other.ambient;

        objects.clear();
        for (Object* obj : other.objects) {
            objects.push_back(obj);
        }

        lights.clear();
        for (Light* light : other.lights) {
            lights.push_back(light);
        }

        return *this;
    }

    void addObject(Object* obj) {
        objects.push_back(obj);
    }

    void addLight(Light* light) {
        lights.push_back(light);
    }

    Color getBackground() const {
        return background;
    }

    Color getAmbient() const {
        return ambient;
    }

    int nbLights() const {
        return lights.size();
    }

    const Light* getLight(int index) const {
        if (index >= 0 && index < lights.size()) {
            return lights[index];
        }
        return nullptr;
    }

    int nbObjects() const {
        return objects.size();
    }

    Object* getObject(int index) const {
        if (index >= 0 && index < objects.size()) {
            return objects[index];
        }
        return nullptr;
    }


    // Retourne un pointeur vers l'objet intersecté le plus proche par le rayon
    // Met à jour le point d'impact passé en paramètre par référence
    Object* closer_intersected(const Ray& ray, Point& impact) const {
        Object* closestObj = nullptr;
        float closestDist = std::numeric_limits<float>::infinity();

        for (Object* obj : objects) {
            Point objImpact;
            if (obj->intersect(ray, objImpact)) {
                Point preVector = objImpact - ray.origin;
                float dist = Vector(preVector.x, preVector.z, preVector.z).norm();
                if (dist < closestDist) {
                    closestObj = obj;
                    closestDist = dist;
                    impact = objImpact;
                }
            }
        }

        return closestObj;
    }
};

#endif // SCENE_HPP
