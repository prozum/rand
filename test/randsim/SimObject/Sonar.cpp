#include "Sonar.h"

Sonar::Sonar(Vector2D Start, uint32_t RayCount, double Angle, double Span, double Length) : angle(Angle), span(Span), ray_count(RayCount) {

    double resolution = Span / (double)RayCount;
    double startAngle = Angle + (span/2);

    for (int i = 0; i < RayCount; ++i) {
        rays.push_back(Ray(Start, Length, Angle + startAngle + (i * resolution)));
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
                dist = (uint32_t)vec.length();
                this->sonar.valid = 1;
            }
        }
    }

    this->sonar.value = (uint16_t)dist;
}