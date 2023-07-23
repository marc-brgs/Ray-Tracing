#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Object.hpp"
#include "Point.hpp"

class Cylinder: public Object {
public:
    bool intersect(const Ray& ray, Point& impact) const {
        Ray r = globalToLocal(ray).normalized();

        float a = r.vector.x * r.vector.x + r.vector.z * r.vector.z;
        float b = 2 * (r.vector.x * r.origin.x + r.vector.z * r.origin.z);
        float c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1.0;
        float delta = b * b - 4 * a * c;

        if (delta < 0)
            return false;

        float t;
        if (delta < 0.0001) {
            t = -b / (2 * a);
        } else {
            t = (-b - std::sqrt(delta)) / (2 * a);
            if (t < 0)
                t = (-b + std::sqrt(delta)) / (2 * a);
        }
        if (t < 0)
            return false;

        Point p = r.origin +  r.vector * t ;
        impact = localToGlobal(p);
        return true;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);
        Point temp=lo - Point(0, lo[1], 0);
        Vector normal = Vector(temp.x,temp.y,temp.z);
        if (normal.norm() > 1)
            return localToGlobal(Ray(lp, Vector(lp[0], 0, lp[2]))).normalized();

        return localToGlobal(Ray(lp, Vector(-lp[0], 0, -lp[2]))).normalized();
    }

    Material getMaterial(const Point& p) const {
        if(!hasTexture) {
            Color ambient(0.5, 0.5, 0.0); // Composante ambiante (jaune crotte de nez)
            Color diffuse(0.5, 0.5, 0.0); // Composante diffuse (jaune crotte de nez)

            Material material(ambient, diffuse, this->specular, this->shininess);
            return material;
        }
        else {
            Point textureCoords = getTextureCoordinates(p);

            // Coordonnées de texture comprises entre 0 et 1
            float u = textureCoords.x;
            float v = textureCoords.y;

            if (texture.empty()) {
                return Material(Color(1.0f, 0.0f, 1.0f), Color(1.0f, 0.0f, 1.0f), Color(1.0f, 0.0f, 1.0f), 0.0f);
            }

            int x = static_cast<int>(u * texture.cols);
            int y = static_cast<int>(v * texture.rows);

            if (x < 0 || x >= texture.cols || y < 0 || y >= texture.rows) {
                return Material(Color(1.0f, 0.0f, 1.0f), Color(1.0f, 0.0f, 1.0f), Color(1.0f, 0.0f, 1.0f), 0.0f);
            }

            cv::Vec3b pixelColor = texture.at<cv::Vec3b>(y, x);

            Color color(pixelColor[2] / 255.0f, pixelColor[1] / 255.0f, pixelColor[0] / 255.0f);

            return Material(color, color, color, this->shininess);
        }
    }

    Point getTextureCoordinates(const Point& p) const {
        Point lp = globalToLocal(p);

        // Convertir les coordonnées cartésiennes en coordonnées cylindriques
        float theta = std::atan2(lp.y, lp.x); // Angle en radians

        // Remap theta pour obtenir les coordonnées de texture enroulées autour du cylindre
        float u = theta / (2 * M_PI) + 0.5; // Mappé sur [0, 1]

        // La coordonnée v n'est pas utilisée car le cylindre est infini le long de l'axe
        float v = 0.0f;

        return Point(u, v, 0);
    }
};


#endif //CYLINDER_HPP