#include "Vector2D.h"

Vector2D::Vector2D() {
    this.x = 0;
    this.y = 0;
}

Vector2D::Vector2D(Vector2D vector) {
    this.x = vector.x;
    this.y = vector.y;
}

Vector2D::Vector2D(uint32_t x, uint32_t y) {
    this.x = x;
    thix.y = y;
}

Vector2D Vector2D::operator+(const Vector2D &rhs, const Vector2D &lhs) {
    return Vector2D(rhs.x + lhs.x, rhs.y + lhs.y);
}

Vector2D Vector2D::operator-(const Vector2D &rhs, const Vector2D &lhs) {
    return Vector2D(rhs.x - lhs.x, rhs.y - lhs.y);
}