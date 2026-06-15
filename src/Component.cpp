#include "Component.h"

Component::Component(double health, double weight, double cost) : health(health), weight(weight), cost(cost) {}

Component::~Component() {}

double Component::getHealth() const noexcept{
    return health;
}

double Component::getWeight() const noexcept{
    return weight;
}

double Component::getCost() const noexcept{
    return cost;
}