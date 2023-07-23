#ifndef CUBE_HPP
#define CUBE_HPP

#include "Entity.hpp"
#include "Object.hpp"
#include "Vector.hpp"
#include "Point.hpp"

class Cube : public Object {
public:
    Cube() {}

    float interSide(const Ray& r, int dim, float offset) const {
        float t = -1;
        if (r.vector[dim] < 0.00001 && r.vector[dim] > -0.00001)
            return -1;
        t = (offset - r.origin[dim]) / r.vector[dim];
        if (t < 0)
            return -1;
        for (int d = 0; d < 3; d++) {
            if (d == dim)
                continue;
            float x = r.origin[d] + t * r.vector[d];
            if (x < -1 || x > 1)
                return -1;
        }
        return t;
    }

    bool intersect(const Ray& ray, Point& impact) const {
        Ray r = globalToLocal(ray).normalized();

        float mint = -1;
        float offsets[] = { -1, 1 };
        for (int d = 0; d < 3; d++) {
            for (int o = 0; o < 2; o++) {
                float t = interSide(r, d, offsets[o]);
                if (t >= 0 && (mint < 0 || mint > t)) {
                    mint = t;
                }
            }
        }

        if (mint >= 0) {
            impact = localToGlobal(r.origin + r.vector * mint);
            return true;
        }

        return false;
    }

    Ray getNormal(const Point& p, const Point& o) const {
        Point lp = globalToLocal(p);
        Point lo = globalToLocal(o);
        Vector v(0, 0, 0);

        if (lp[0] > 0.999)
            v[0] = 1.0;
        else if (lp[0] < -0.999)
            v[0] = -1.0;
        else if (lp[1] > 0.999)
            v[1] = 1.0;
        else if (lp[1] < -0.999)
            v[1] = -1.0;
        else if (lp[2] > 0.999)
            v[2] = 1.0;
        else if (lp[2] < -0.999)
            v[2] = -1.0;

        if (lo[0] < 1 && lo[0] > -1 && lo[1] < 1 && lo[1] > -1 && lo[2] < 1 && lo[2] > -1)
            return localToGlobal(Ray(lp, v)).normalized();
        return localToGlobal(Ray(lp, v)).normalized();
    }

    Material getMaterial(const Point& p) const {
        if(!hasTexture) {
            Color ambient(0.0, 1.0, 0.0); // Composante ambiante (vert)
            Color diffuse(0.0, 1.0, 0.0); // Composante diffuse (vert)

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
        if(lp[0]>0.999 || lp[0]<-0.999)return Point(lp[2]/2 + 0.5,lp[1]/2 + 0.5,0);
        if(lp[1]>0.999 || lp[1]<-0.999)return Point(lp[0]/2 + 0.5,lp[2]/2 + 0.5,0);
        if(lp[2]>0.999 || lp[2]<-0.999)return Point(lp[0]/2 + 0.5,lp[1]/2 + 0.5,0);
        return Point(0,0,0);
    }
};

#endif // CUBE_HPP