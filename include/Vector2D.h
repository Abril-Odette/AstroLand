#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
    public:
        double x;
        double y;

        Vector2D();
        Vector2D(double x, double y);

        Vector2D add(const Vector2D& other) const;
        Vector2D scale(double factor) const;
        double magnitude() const;
        Vector2D normalize() const;

        Vector2D operator+(const Vector2D& other) const;
        Vector2D operator*(double factor) const;
        bool operator==(const Vector2D& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
    
};

#endif