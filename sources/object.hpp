#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Entity.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Object : public Entity {
public:
    virtual Material getMaterial(const Point& p) const = 0;
    virtual Ray getNormal(const Point& p, const Point& o) const = 0;
    virtual bool intersect(const Ray& ray, Point& impact) const = 0;
};

#endif // OBJECT_HPP