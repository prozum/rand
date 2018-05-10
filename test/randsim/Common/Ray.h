#pragma once

#include "SimObject/SimObject.h"
#include "Vector2D.h"

class Ray : public SimObject {
    double Length;
    void update(double Angle);

  public:
    Ray(Vector2D Origin, double Angle, double Length);
    void update(Vector2D Origin, double Angle);
    void update();
    void draw();

    Vector2D Origin;
    Vector2D Direction;
    Vector2D Inverted;
    double Angle;
};