#pragma once

#include <vector>
#include <stdint.h>

#include "Block.h"

extern "C" {
#include "sonar/sonar.h"
}

class Drone;

class Sonar : public SimObject {
private:
    Drone &Drn;
    double Length;
    double Span;
    uint32_t RayCount;

    void calcDist(std::vector<Block> & Blocks);
    void updateRays(Vector2D Pos, double Angle);
public:
    sonar_t Struct;
    std::vector<Ray> Rays;

    Sonar(Drone &Drn, uint32_t RayCount, double Span, double Length);

    void update();
    void draw();
};