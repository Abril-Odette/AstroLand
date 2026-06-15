#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
    protected:
        double health;
        double weight;
        double cost;

    public:
        Component(double health, double weight, double cost);
        virtual ~Component();

        double getHealth() const noexcept;
        double getWeight() const noexcept;
        double getCost() const noexcept;

        virtual void activate() = 0;
    
};

#endif