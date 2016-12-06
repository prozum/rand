#include "Sonar.h"

Sonar::Sonar(uint32_t ray_count, double angle) : angle(angle), ray_count(ray_count) {
    for (int i = 0; i < ray_count; ++i) {
        rays.push_back(Ray());
    }
}

void Sonar::calcDist(std::vector<Block> blocks) {
    Vector2D vec;
    uint32_t dist = UINT32_MAX;
    this->sonar.valid = 0;

    for (auto b : blocks) {
        for (auto r : rays) {
            auto res = b.intersection(r, vec);

            if (res) {
                dist = vec.length();
                this->sonar.valid = 1;
            }
        }
    }

    this->sonar.value = dist;
}