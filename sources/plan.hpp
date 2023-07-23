#ifndef PLAN_HPP
#define PLAN_HPP

#include "Object.hpp"
#include "Point.hpp"
#include "Material.hpp"

class Plan : public Object {
public:
    Plan() {}

    bool intersect(const Ray& ray, Point& impact) const {
        Ray local_ray = globalToLocal(ray);
        float t = -local_ray.origin.getZ() / local_ray.vector.getZ();
        Point local_intersection = local_ray.origin + local_ray.vector * t;

        if (t >= 0) {
            impact = localToGlobal(local_intersection);
            return true;
        }

        return false;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);
        float z = 1;
        if (lo.z < 0)
            z = -1;
        return localToGlobal(Ray(lp, Vector(0, 0, z))).normalized();
    }

    Material getMaterial(const Point& p) const {
        if(!hasTexture) {
            Color ambient(0.6, 0.6, 0.6); // Composante ambiante (noir)
            Color diffuse(0.6, 0.6, 0.6); // Composante diffuse (rouge)

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
        float scale = 2;
        float x = lp[0] / scale;
        float y = lp[1] / scale;

        while (x >= 1) x -= 1;
        while (y >= 1) y -= 1;
        while (x < 0) x += 1;
        while (y < 0) y += 1;

        return Point(x, y, 0);
    }
};

#endif // PLAN_HPP