#ifndef PLANET_H
#define PLANET_H

#include "Astro.h"

class Planet : public Astro {
private:
    bool hasAtmosphere;
    double atmosphereDensity;

public:
    Planet(const std::string& name, double mass, double radius, const Vector2D& position, bool hasAtmosphere, double atmosphereDensity);
    ~Planet();

    bool getHasAtmosphere() const;
    double getAtmosphereDensity() const;
    
    double surfaceGravity() const override;
};

#endif