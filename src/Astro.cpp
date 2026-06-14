#include "Astro.h"

#include <vector>
#include <string>

Astro::Astro(const std::string& name, double mass, double radius, const Vector2D& position)
    : name(name), mass(mass), radius(radius), position(position) {}

Astro::~Astro() {}

const std::string& Astro::getName() const noexcept {
    return name;
}

double Astro::getMass() const noexcept {
    return mass;
}

double Astro::getRadius() const noexcept {
    return radius;
}

const Vector2D& Astro::getPosition() const noexcept {
    return position;
}