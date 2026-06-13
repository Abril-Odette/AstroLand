#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() : x(0.0), y(0.0) {}

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D Vector2D::add(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::scale(double factor) const {
    return Vector2D(x * factor, y * factor);
}

double Vector2D::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const {
    double mag = magnitude();
    if (mag == 0) {
        return Vector2D(0.0, 0.0);
    }
    return Vector2D(x / mag, y / mag);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return add(other);
}

Vector2D Vector2D::operator*(double factor) const {
    return scale(factor);
}

bool Vector2D::operator==(const Vector2D& other) const {
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}   