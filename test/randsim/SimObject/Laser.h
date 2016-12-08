#pragma once

#include <vector>

#include "Block.h"

extern "C" {
#include "laser/laser.h"
}

class Laser {
private:
    double Length;
    double Angle;
    Vector2D Pos;

    void update(Vector2D Origin, double Angle);
public:
    std::vector<Ray> Rays;
    laser_t LaserStruct;

    Laser(Vector2D Origin, double Length, double Angle);
    void calcDist(std::vector<Block>& Blocks, Vector2D& Origin, double Angle);
    void draw();
};

