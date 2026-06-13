#include "Thruster.h"
#include "Component.h"

Thruster::Thruster(double health, double weight, double cost, double thrust, double fuelConsumption, const Vector2D& direction)
    : Component(health, weight, cost), thrust(thrust), fuelConsumption(fuelConsumption), direction(direction) {}

double Thruster::getThrust() const {
    return thrust;
}

double Thruster::getFuelConsumption() const {
    return fuelConsumption;
}

const Vector2D& Thruster::getDirection() const {
    return direction;
}

void Thruster::activate() {
std::cout << "Activating thruster with thrust: " << thrust << " and fuel consumption: " << fuelConsumption << std::endl;
}