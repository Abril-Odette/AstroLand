#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <cmath>

class Vector2D {
    public:
        double x;
        double y;

        Vector2D() noexcept;
        Vector2D(double x, double y) noexcept;

        Vector2D add(const Vector2D& other) const noexcept;
        Vector2D scale(double factor) const noexcept;
        double magnitude() const noexcept;
        Vector2D normalize() const noexcept;

        Vector2D operator+(const Vector2D& other) const noexcept;
        Vector2D operator-(const Vector2D& other) const noexcept;
        Vector2D operator*(double factor) const noexcept;
        bool operator==(const Vector2D& other) const noexcept;
        bool operator!=(const Vector2D& other) const noexcept;
        bool operator<(const Vector2D& other) const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
    
};

#endif