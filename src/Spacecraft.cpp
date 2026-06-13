#include <vector>
#include <string>

#include "Spacecraft.h"
#include "Vector2D.h"
#include"Component.h"
#include "Astro.h"

Spacecraft::Spacecraft(const std::string& name, const Vector2D& position, const Vector2D& velocity, double mass, double fuelCapacity)
    : name(name), position(position), velocity(velocity), mass(mass), fuelCapacity(fuelCapacity), landed(false) {}

const std::string& Spacecraft::getName() const {
    return name;
}

const Vector2D& Spacecraft::getPosition() const {
    return position;
}

const Vector2D& Spacecraft::getVelocity() const {
    return velocity;
}

double Spacecraft::getMass() const {
    return mass;
}

double Spacecraft::getFuelCapacity() const {
    return fuelCapacity;
}

bool Spacecraft::isLanded() const {
    return landed;
}

void Spacecraft::addComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component));
}

