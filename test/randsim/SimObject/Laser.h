#pragma once

#include <vector>

#include "Block.h"

extern "C" {
#include "laser/laser.h"
}

class Drone;

class Laser : public SimObject {
private:
    Drone &Drn;
    double Length;

    void updateRays(Vector2D Pos, double Angle);
    void calcDist(std::vector<Block>& Blocks);
public:
    std::vector<Ray> Rays;
    laser_t Struct;

    Laser(Drone &Drn, double Length);

    void update();
    void draw();
};

