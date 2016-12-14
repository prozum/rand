#include "Laser.h"
#include "Drone.h"

Laser::Laser(Drone &Drn, double Length) : Drn(Drn),
                                          SimObject(Drn.Pos),
                                          Length(Length) {

    for (int i = 0; i < 3; ++i) {
        Rays.push_back(Ray(Drn.Pos, Length, Drn.Angle));
    }

    Struct = *laser_init(TX1);
}

void Laser::calcDist(std::vector<Block>& Blocks) {
    Vector2D Res;
    bool Intersects;

    Struct.val_left = 2200;
    Struct.val_front = 2200;
    Struct.val_right = 2200;

    for (auto &B : Blocks) {
        // Laser cannot sense windows
        if (B.Type == BlockType::Window)
            continue;

        Intersects = B.intersect(Rays[0], Res);
        if (Intersects) Struct.val_left = std::min(Struct.val_left, (uint16_t)Res.length());

        Intersects = B.intersect(Rays[1], Res);
        if (Intersects) Struct.val_front = std::min(Struct.val_front, (uint16_t)Res.length());

        Intersects = B.intersect(Rays[2], Res);
        if (Intersects) Struct.val_right = std::min(Struct.val_right, (uint16_t)Res.length());
    }

    if (Struct.val_left > Length) Struct.val_left = 2200;
    if (Struct.val_front > Length) Struct.val_front = 2200;
    if (Struct.val_right > Length) Struct.val_right = 2200;
}

void Laser::updateRays(Vector2D Pos, double Angle) {
    this->Pos = Pos;
    Rays[0].update(Pos, Angle + (M_PI / 2));
    Rays[1].update(Pos, Angle);
    Rays[2].update(Pos, Angle - (M_PI / 2));
}

void Laser::draw() {
    for (auto &Ray : Rays) {
        Ray.draw();
    }
}

void Laser::update() {
    updateRays(Drn.Pos, Drn.Angle);
    calcDist(Sim->Blocks);
}
