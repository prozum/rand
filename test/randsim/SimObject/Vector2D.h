#pragma once

#include <stdint.h>
#include <cmath>

class Vector2D {
public:
    Vector2D();
    Vector2D(const Vector2D&);
    Vector2D(double X, double Y);
    Vector2D(int X, int Y);

    Vector2D operator-(const Vector2D &Arg);
    Vector2D operator+(const Vector2D &Arg);
    double determinant(Vector2D V);
    double dot(Vector2D);
    double length();

    double X;
    double Y;
};