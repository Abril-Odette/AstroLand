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

        double getHealth() const;
        double getWeight() const;
        double getCost() const;

        virtual void activate() = 0;
    
};

#endif