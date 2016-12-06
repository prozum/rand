#pragma once

#include <stdint.h>
#include <cmath>

class Vector2D {
public:
    Vector2D();
    Vector2D(const Vector2D&);
    Vector2D(int32_t x, int32_t y);

    Vector2D operator-(const Vector2D &arg);
    Vector2D operator+(const Vector2D &arg);
    int32_t determinant(Vector2D);
    int32_t dot(Vector2D);
    double length();

    int32_t x;
    int32_t y;
};