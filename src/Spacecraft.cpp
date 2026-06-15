#include <iostream>
#include <cmath>

#include "Spacecraft.h"
#include "Thruster.h"
#include "FuelSensor.h"

Spacecraft::Spacecraft(const std::string& name, const Vector2D& position, double mass, double fuel)
    : name(name), position(position), mass(mass), fuel(fuel), landed(false), crashed(false), thrusterActive(false)
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

bool Spacecraft::isCrashed() const noexcept { 
    return crashed; 
}

bool Spacecraft::isThrusterActive() const noexcept {
    return thrusterActive;
}

void Spacecraft::addComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component));
}

void Spacecraft::applyGravity(const Astro& body, double dt) {
    double g = body.surfaceGravity();
    velocity = velocity + Vector2D(0.0,-g).scale(dt);
}

void Spacecraft::applyThrust(double dt) {
    for (const auto& comp : components) {
        FuelSensor* sensor = dynamic_cast<FuelSensor*>(comp.get());
        if (sensor) sensor->updateFuel(fuel);
    }

    if (!thrusterActive || fuel <= 0.0) return;

    for (const auto& comp : components) {
        Thruster* thruster = dynamic_cast<Thruster*>(comp.get());
        if (!thruster) continue;

        double fuelNeeded = thruster->getFuelConsumption()* dt;
        if (fuel < fuelNeeded) continue;

        thruster->activate();

        Vector2D thrustDir = thruster->getDirection().normalize();
        double accelMag = thruster ->getThrust() / mass;
        velocity = velocity + thrustDir.scale(accelMag * dt);
        fuel -= fuelNeeded;
    }
}

void Spacecraft::update(const Astro& body, double dt) {
    if (landed || crashed) return;

    applyGravity(body, dt);
    applyThrust(dt);

    position = position + velocity.scale(dt);

}

bool Spacecraft::checkLanding(const Astro& body) {
    if (landed || crashed) return true;

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

    return landed || crashed;
}