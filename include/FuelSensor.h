#ifndef FUELSENSOR_H
#define FUELSENSOR_H

#include "Component.h"
#include <string>
#include <iostream>

class FuelSensor : public Component {
    private:
        double fuelCapacity;
        double currentFuel;

    public:
        FuelSensor(double health, double weigth, double cost, double fuelCapacity);
        ~FuelSensor() override = default;

        void updateFuel (double fuel) noexcept;
        double getFuelPercentage() const noexcept;
        std:: string getStatus () const;

        void activate() override;
};

#endif