#include "Sonar.h"
#include "Drone.h"

Sonar::Sonar(Drone &Drn, uint32_t RayCount, double Span, double Length) : Drn(Drn),
                                                                          SimObject(Drn.Pos),
                                                                          Span(Span), RayCount(RayCount), Length(Length) {
    Struct = *sonar_init(P0, P1);

    for (int i = 0; i < RayCount; ++i) {
        Rays.push_back(Ray(Drn.Pos, Length, Drn.Angle));
    }
}

void Sonar::calcDist(std::vector<Block> &Blocks) {
    Vector2D Res;
    double Dist = INFINITY;
    Struct.valid = 0;

    for (auto &Block : Blocks) {
        for (auto &Ray : Rays) {
            bool Intersects = Block.intersect(Ray, Res);
            if (Intersects)
                Dist = std::min(Dist, Res.length());
        }

        if (Dist <= Length) {
            Struct.value = (uint16_t)Dist;
            Struct.valid = 1;
        }
    }
}

void Sonar::updateRays(Vector2D Pos, double Angle) {
    this->Pos = Pos;
    double Resolution = Span / RayCount;
    double StartAngle = Angle - (Span / 2);

    for (int i = 0; i < RayCount; ++i) {
        Rays[i].update(Pos, StartAngle + (i * Resolution));
    }
}

void Sonar::update() {
    updateRays(Drn.Pos, Drn.Angle);
    calcDist(Sim->Blocks);
}

void Sonar::draw() {
    for (auto &Ray : Rays) {
        Ray.draw();
    }
}

