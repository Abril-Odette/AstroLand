#include "Moon.h"

Moon::Moon(const std::string& name, double mass, double radius, const Vector2D& position, double orbitalRadius, double orbitalPeriod)
    : Astro(name, mass, radius, position), orbitalRadius(orbitalRadius), orbitalPeriod(orbitalPeriod) {}

double Moon::getOrbitalRadius() const noexcept {
    return orbitalRadius;
}

double Moon::getOrbitalPeriod() const noexcept {
    return orbitalPeriod;
}

double Moon::surfaceGravity() const {
    const double G = 6.67430e-11; // Gravitational constant
    return G * mass / (radius * radius);
}