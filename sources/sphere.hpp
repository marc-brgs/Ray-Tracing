#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Entity.hpp"
#include "Object.hpp"
#include "Vector.hpp"

class Sphere : public Object {
public:
    Sphere() {}

    bool intersect(const Ray& ray, Point& impact) const {
        Ray local_ray = globalToLocal(ray);

        float a = local_ray.vector.dot(local_ray.vector);
        float b = 2 * local_ray.vector.dot(Vector(local_ray.origin.x, local_ray.origin.y, local_ray.origin.z));
        float c = local_ray.origin.dot(local_ray.origin) - 1.0;
        float delta = b * b - 4 * a * c;

        if (delta < 0) {
            return false;
        }

        float t1 = (-b - sqrt(delta)) / (2 * a);
        float t2 = (-b + sqrt(delta)) / (2 * a);

        float t = t1 < t2 ? t1 : t2; // min
        if (t > 0) {
            Point local_intersection = local_ray.origin + (local_ray.vector * t);
            impact = localToGlobal(local_intersection);
            return true;
        }

        t = t1 > t2 ? t1 : t2; // max
        if (t > 0) {
            Point local_intersection = local_ray.origin + (local_ray.vector * t);
            impact = localToGlobal(local_intersection);
            return true;
        }

        return false;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);

        Vector normal = Vector(lp.x, lp.y, lp.z).normalized();

        if (Vector(lo.x, lo.y, lo.z).norm() < 1) {
            normal = -normal;
        }

        return localToGlobal(Ray(lp, normal)).normalized();
    }

    Material getMaterial(const Point& p) const {
        if(!hasTexture) {
            Color ambient(0.0, 0.0, 0.0); // Composante ambiante (noir)
            Color diffuse(1.0, 0.0, 0.0); // Composante diffuse (rouge)

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

    Point getTextureCoordinates(const Point& p)const{
        Point lp = globalToLocal(p);
        float rho = std::sqrt(lp.dot(lp));
        float theta = std::atan2(lp[1], lp[0]);
        float sigma = std::acos(lp[2]/rho);
        float x = -theta/(2*M_PI)+0.5;
        float y = sigma/M_PI;
        return Point(x,y,0);
    }
};

#endif // SPHERE_HPP