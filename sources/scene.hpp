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
    // Constructeur
    Scene(const Color& background, const Color& ambient)
            : background(background), ambient(ambient) {}

    // Destructeur
    ~Scene() {
        // Libérer la mémoire des objets et des lumières
        for (Object* obj : objects) {
            delete obj;
        }
        for (Light* light : lights) {
            delete light;
        }
    }

    // Ajouter un objet à la scène
    void addObject(Object* obj) {
        objects.push_back(obj);
    }

    // Ajouter une lumière à la scène
    void addLight(Light* light) {
        lights.push_back(light);
    }

    // Retourne la couleur d'arrière-plan
    Color getBackground() const {
        return background;
    }

    // Retourne la valeur de la lumière ambiante
    Color getAmbient() const {
        return ambient;
    }

    // Retourne le nombre de lumières dans la scène
    int nbLights() const {
        return lights.size();
    }

    // Retourne un pointeur vers la nième lumière
    const Light* getLight(int index) const {
        if (index >= 0 && index < lights.size()) {
            return lights[index];
        }
        return nullptr;
    }

    // Retourne le nombre de lumières dans la scène
    int nbObjects() const {
        return objects.size();
    }

    // Retourne un pointeur vers le nième objet dans la scène
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
