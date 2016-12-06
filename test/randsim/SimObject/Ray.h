#pragma once

#include "Vector2D.h"

class Ray {
    double length;
    double angle;
public:
    Ray(Vector2D Origin, double Angle, double Length);
    void update(double Angle);
    void update(Vector2D Origin, double Angle);

    Vector2D Origin;
    Vector2D Direction;
};