#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <vector>
#include <memory>

#include "Vector2D.h"
#include "Component.h"

class Spacecraft {
    private:
        std::string name;
        Vector2D position;
        Vector2D velocity;
        double mass;
        double fuelCapacity;
        bool landed;
        std::vector<std::unique_ptr<Component>> components;

    public:
        Spacecraft(const std::string& name, const Vector2D& position, const Vector2D& velocity, double mass, double fuelCapacity);

        const std::string& getName() const;
        const Vector2D& getPosition() const;
        const Vector2D& getVelocity() const;
        double getMass() const;
        double getFuelCapacity() const;
        bool isLanded() const;

        void addComponent(std::unique_ptr<Component> component);
};

#endif