#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() noexcept : x(0.0), y(0.0) {}

Vector2D::Vector2D(double x, double y) noexcept : x(x), y(y) {}

Vector2D Vector2D::add(const Vector2D& other) const noexcept {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::scale(double factor) const noexcept {
    return Vector2D(x * factor, y * factor);
}

double Vector2D::magnitude() const noexcept {
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const noexcept {
    double mag = magnitude();
    if (mag == 0) {
        return Vector2D(0.0, 0.0);
    }
    return Vector2D(x / mag, y / mag);
}

Vector2D Vector2D::operator+(const Vector2D& other) const noexcept {
    return add(other);
}

Vector2D Vector2D::operator-(const Vector2D& other) const noexcept {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double factor) const noexcept {
    return scale(factor);
}

bool Vector2D::operator==(const Vector2D& other) const noexcept {
    return x == other.x && y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const noexcept {
    return !(*this == other);
}

bool Vector2D::operator<(const Vector2D& other) const noexcept {
    return magnitude() < other.magnitude();
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}   