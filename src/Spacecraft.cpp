#include <iostream>
#include <cmath>

#include "Spacecraft.h"
#include "Thruster.h"

Spacecraft::Spacecraft(const std::string& name, const Vector2D& position, const Vector2D& velocity, double mass, double fuel)
    : name(name), position(position), velocity(0.0, 0.0), mass(mass), fuel(fuel), landed(false)
{
    if (name.empty())
        throw AstrolandException("Spacecraft name cannot be empty.");
    if (mass <= 0.0)
        throw AstrolandException("Spacecraft mass must be positive. Got: " + std::to_string(mass));
    if (fuel < 0.0)
        throw AstrolandException("Spacecraft fuel cannot be negative. Got: " + std::to_string(fuel));
}

const std::string& Spacecraft::getName() const noexcept {
    return name;
}

const Vector2D& Spacecraft::getPosition() const noexcept {
    return position;
}

const Vector2D& Spacecraft::getVelocity() const noexcept {
    return velocity;
}

double Spacecraft::getMass() const noexcept {
    return mass;
}

double Spacecraft::getFuel() const noexcept {
    return fuel;
}

bool Spacecraft::isLanded() const noexcept {
    return landed;
}

void Spacecraft::addComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component));
}

void Spacecraft::applyGravity(const Astro& body, double dt) {
    double g = body.surfaceGravity();
    Vector2D gravityAcceleration(0.0, -g);
    velocity = velocity + gravityAcceleration.scale(dt);
}

void Spacecraft::applyThrust(double dt) {
    if (fuel <= 0.0) return;

    for (const auto& comp : components) {
        Thruster* thruster = dynamic_cast<Thruster*>(comp.get());
        if (thruster == nullptr) continue;

        double fuelNeeded = thruster->getFuelConsumption() * dt;
        if (fuel < fuelNeeded) continue;

        thruster->activate();

        Vector2D thrustDirection = thruster->getDirection().normalize();
        double accelerationMagnitude = thruster->getThrust() / mass;

        velocity = velocity + thrustDirection.scale(accelerationMagnitude * dt);
        fuel -= fuelNeeded;
    }
}

void Spacecraft::update(const Astro& body, double dt) {
    if (landed) return;

    applyGravity(body, dt);
    applyThrust(dt);

    position = position + velocity.scale(dt);

}

bool Spacecraft::checkLanding(const Astro& body) {
    if (landed) return true;

    double surfaceY = body.getPosition().y + body.getRadius();

    if (position.y <= surfaceY) {
        position.y = surfaceY;

        double speed = velocity.magnitude();
        const double MAX_SAFE_SPEED = 5.0;

        if (speed <= MAX_SAFE_SPEED) {
            landed = true;
            std::cout << "[Landing] Safe landing! Speed: " << speed << " m/s" << std::endl;
        } else {
            landed = true;
            std::cout << "[Landing] Crash! Speed: " << speed << " m/s" << std::endl;
        }

        velocity = Vector2D(0.0, 0.0);
    }

    return landed;
}