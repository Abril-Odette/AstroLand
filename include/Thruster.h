#ifndef THRUSTER_H
#define THRUSTER_H

#include "Component.h"
#include "Vector2D.h"

    class Thruster: public Component {
    private:
        double thrust;
        double fuelConsumption;
        Vector2D direction;

    public:
        Thruster(double health, double weight, double cost, double thrust, double fuelConsumption, const Vector2D& direction);

        double getThrust() const noexcept;
        double getFuelConsumption() const noexcept;
        const Vector2D& getDirection() const noexcept;

        void activate() override;
};

#endif