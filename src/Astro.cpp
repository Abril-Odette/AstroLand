#include "Astro.h"

#include <vector>
#include <string>

Astro::Astro(const std::string& name, double mass, double radius, const Vector2D& position)
    : name(name), mass(mass), radius(radius), position(position) {}

Astro::~Astro() {}

std::string Astro::getName() const {
    return name;
}
double Astro::getMass() const {
    return mass;
}

double Astro::getRadius() const {
    return radius;
}

const Vector2D& Astro::getPosition() const {
    return position;
}