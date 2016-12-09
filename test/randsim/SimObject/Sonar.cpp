#include "Sonar.h"

Sonar::Sonar(Vector2D Origin, uint32_t RayCount, double Angle, double Span, double Length)
        : Length(Length), Angle(Angle), Span(Span), RayCount(RayCount) {

    for (int i = 0; i < RayCount; ++i) {
        Rays.push_back(Ray(Origin, Length, Angle));
    }
}

void Sonar::calcDist(std::vector<Block> &Blocks, Vector2D& Origin, double Angle) {
    Vector2D Res;
    double Dist = INFINITY;
    this->Struct.valid = 0;

    update(Origin, Angle);

    for (auto &Block : Blocks) {
        for (auto &Ray : Rays) {
            bool Intersects = Block.intersection(Ray, Res);
            if (Intersects) Dist = std::min(Dist, Res.length());
        }

        if (Dist <= Length) {
            Struct.value = Dist;
            Struct.valid = 1;
        }
    }
}

void Sonar::update(Vector2D& Origin, double Angle) {
    double Resolution = Span / (double)RayCount;
    double StartAngle = Angle - (Span/2);

    for (int i = 0; i < RayCount; ++i) {
        Rays[i].update(Origin, StartAngle + (i * Resolution));
    }
}

void Sonar::draw() {
    for (auto &Ray : Rays) {
        Ray.draw();
    }
}