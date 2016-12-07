#pragma once

#include <vector>

#include "Block.h"

class Laser {
public:
    laser_t LaserStruct;
    std::vector<Ray> rays;

    Laser(uint32_t, double, double, double);
    void calcDist(std::vector<Block>);
};

