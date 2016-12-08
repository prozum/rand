#pragma once

#include <vector>
#include <stdint.h>

#include "Block.h"

extern "C" {
#include "sonar/sonar.h"
}

class Sonar {
private:
    double Length;
    double Angle;
    double Span;
    uint32_t RayCount;
    Vector2D Pos;
    void update(Vector2D& Origin, double Angle);
public:
    sonar_t Struct;
    std::vector<Ray> Rays;

    Sonar(Vector2D Origin, uint32_t RayCount, double Angle, double Span, double Length);
    void calcDist(std::vector<Block> & Blocks, Vector2D& Origin, double Angle);
    void draw();
};