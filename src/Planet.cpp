#include "Planet.h"

Planet::Planet(const std::string& name, double mass, double radius, const Vector2D& position, bool hasAtmosphere, double atmosphereDensity)
    : Astro(name, mass, radius, position), hasAtmosphere(hasAtmosphere), atmosphereDensity(atmosphereDensity) {}

bool Planet::getHasAtmosphere() const noexcept{
    return hasAtmosphere;
}

double Planet::getAtmosphereDensity() const noexcept{
    return atmosphereDensity;
}

double Planet::surfaceGravity() const {
    const double G = 6.67430e-11; // Gravitational constant
    return G * mass / (radius * radius);
}