#include "Vector2D.h"

Vector2D::Vector2D() : x(0), y(0) { }

Vector2D::Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y) { }

Vector2D::Vector2D(int32_t x, int32_t y) : x(x), y(y) { }

Vector2D Vector2D::operator+(const Vector2D &arg) {
    return Vector2D(this->x + arg.x, this->y + arg.y);
}

Vector2D Vector2D::operator-(const Vector2D &arg) {
    return Vector2D(this->x - arg.x, this->y - arg.y);
}

int32_t Vector2D::determinant(Vector2D v) {
    return x*v.y - y*v.x;
}

int32_t Vector2D::dot(Vector2D v) {
    return x*v.x + y*v.y;
}

double Vector2D::length() {
    return sqrt(pow(x, 2) + pow(y, 2));
}