#pragma once

#include <vector>
#include <stdint.h>

#include "Block.h"

class Sonar {
private:
    double angle;
    uint32_t ray_count;
public:
    sonar_t sonar;
    std::vector<Ray> rays;

    Sonar(uint32_t, double);
    void calcDist(std::vector<Block>);
};