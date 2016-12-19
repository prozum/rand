#pragma once

#include <cmath>
#include <stdint.h>

class Vector2D {
  public:
    Vector2D();
    Vector2D(const Vector2D &);
    Vector2D(double X, double Y);
    Vector2D(int X, int Y);

    Vector2D operator-(const Vector2D &Arg);
    Vector2D operator+(const Vector2D &Arg);
    Vector2D operator*(const double &Arg);
    Vector2D invert();
    double determinant(Vector2D &);
    double dot(Vector2D &);
    double length();
    void compose(double Length, double Angle);

    double X;
    double Y;
};