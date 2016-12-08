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
    laser_t LaserStruct;
    std::vector<Ray> Rays;

    Laser(Vector2D Origin, double Length, double Angle);
    void calcDist(std::vector<Block>& Blocks, Vector2D& Origin, double Angle);
    void draw();
};

