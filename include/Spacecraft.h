#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "Vector2D.h"
#include "Component.h"
#include "Thruster.h"
#include "Astro.h"
#include "AstrolandException.h"

class Spacecraft {
    private:
        std::string name;
        Vector2D position;
        Vector2D velocity;
        double mass;
        double fuel;
        bool landed;
        std::vector<std::unique_ptr<Component>> components;

    public:
        Spacecraft(const std::string& name, const Vector2D& position, const Vector2D& velocity, double mass, double fuelCapacity);
        ~Spacecraft();

        const std::string& getName() const noexcept;
        const Vector2D& getPosition() const noexcept;
        const Vector2D& getVelocity() const noexcept;
        double getMass() const noexcept;
        double getFuel() const noexcept;
        bool isLanded() const noexcept;

        void addComponent(std::unique_ptr<Component> component);

        void applyGravity(const Astro& body, double dt);
        void applyThrust(const double dt);
        void update(const Astro& body, double dt);
        bool checkLanding(const Astro& body);

};

#endif