#pragma once

#include <vector>
#include <stdint.h>

#include "Block.h"

class Sonar {
private:
    double Length;
    double Angle;
    double Span;
    uint32_t RayCount;
    Vector2D Pos;
public:
    sonar_t SonarStruct;
    std::vector<Ray> Rays;

    Sonar(Vector2D Start, uint32_t RayCount, double Angle, double Span, double Length);
    void calcDist(std::vector<Block> &, Vector2D&, double);
    void update(Vector2D&, double);
};