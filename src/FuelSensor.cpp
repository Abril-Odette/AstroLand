#include "FuelSensor.h"

FuelSensor::FuelSensor(double health, double weight, double cost, double fuelCapacity)
: Component (health, weight, cost), fuelCapacity(fuelCapacity), currentFuel(fuelCapacity){}

void FuelSensor::updateFuel(double fuel) noexcept {
    currentFuel = fuel;
}

double FuelSensor::getFuelPercentage() const noexcept {
    if (fuelCapacity <= 0.0) return 0.0;
    return (currentFuel / fuelCapacity) * 100.0;
}

std::string FuelSensor::getStatus() const {
    double pct = getFuelPercentage();
    if (pct > 50.0) return "OK";
    if (pct > 20.0) return "LOW";
    return "CRITICAL";
}

void FuelSensor::activate() {
    std::cout << "[FuelSensor] Fuel: "<< getFuelPercentage()
              << "% - " << getStatus() << std::endl;
}