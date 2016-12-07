#pragma once

#include <vector>
#include <stdint.h>

#include "Block.h"

class Sonar {
private:
    double length;
    double angle;
    double span;
    uint32_t ray_count;
    Vector2D pos;
public:
    sonar_t sonar;
    std::vector<Ray> rays;

    Sonar(Vector2D Start, uint32_t RayCount, double Angle, double Span, double Length);
    void calcDist(std::vector<Block>);
    void update(Vector2D& Position);
};