#pragma once

#include <stdint>

class Vector2D {
public:
    Vector2D();
    Vector2D(Vector2D vector);
    Vector2D(uint32_t x, uint32_t y);

    Vector2D operator-(const Vector2D &rhs, const Vector2D &lhs);
    Vector2D operator+(const Vector2D &rhs, const Vector2D &lhs);

    uint32_t x;
    uint32_t y;
};