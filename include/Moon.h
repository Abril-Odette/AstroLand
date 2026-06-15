#ifndef MOON_H
#define MOON_H

#include "Astro.h"

class Moon : public Astro {
    private:
        double orbitalRadius;
        double orbitalPeriod;

    public:
        Moon(const std::string& name, double mass, double radius, const Vector2D& position, double orbitalRadius, double orbitalPeriod);
        ~Moon() override = default;

        double getOrbitalRadius() const noexcept;
        double getOrbitalPeriod() const noexcept;

        double surfaceGravity() const override;
    
};

#endif