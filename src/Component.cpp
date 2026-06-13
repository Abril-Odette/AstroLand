#include "Component.h"

Component::Component(double health, double weight, double cost) : health(health), weight(weight), cost(cost) {}

Component::~Component() {}

double Component::getHealth() const {
    return health;
}

double Component::getWeight() const {
    return weight;
}

double Component::getCost() const {
    return cost;
}