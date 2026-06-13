#ifndef ASTRO_H
#define ASTRO_H

#include <string>
#include "Vector2D.h"

class Astro {
protected:
    std::string name;
    double mass;
    double radius;
    Vector2D position;

public:
    Astro(const std::string& name, double mass, double radius, const Vector2D& position);
    virtual ~Astro();

    std::string getName() const;
    double getMass() const;
    double getRadius() const;
    const Vector2D& getPosition() const;

    virtual double surfaceGravity() const = 0;
};

#endif