#include "Sonar.h"

Sonar::Sonar(Vector2D Start, uint32_t RayCount, double Angle, double Span, double Length)
        : length(length), angle(Angle), span(Span), ray_count(RayCount) {

    double resolution = Span / (double)RayCount;
    double startAngle = Angle + (span/2);

    for (int i = 0; i < RayCount; ++i) {
        rays.push_back(Ray(Start, Length, Angle + startAngle + (i * resolution)));
    }
}

void Sonar::calcDist(std::vector<Block> blocks) {
    Vector2D res;
    double tmp_dist;
    double dist = -INFINITY;
    this->sonar.valid = 0;

    for (auto b : blocks) {
        for (auto r : rays) {
            bool intersects = b.intersection(r, res);
            tmp_dist = res.length();
            if (intersects && tmp_dist < length) {
                dist = std::max(tmp_dist, dist);
                this->sonar.valid = 1;
            }
        }
    }

    this->sonar.value = (uint16_t)dist;
}