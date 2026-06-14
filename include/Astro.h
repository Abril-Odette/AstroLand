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
    virtual ~Astro() noexcept = default;

    const std::string& getName() const noexcept;
    double getMass() const noexcept;
    double getRadius() const noexcept;
    const Vector2D& getPosition() const noexcept;

    virtual double surfaceGravity() const = 0;
};

#endif