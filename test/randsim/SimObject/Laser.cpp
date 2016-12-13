#include "Laser.h"

Laser::Laser(Vector2D Origin, double Length, double Angle)
        : Pos(Origin), Length(Length), Angle(Angle) {

    for (int i = 0; i < 3; ++i) {
        Rays.push_back(Ray(Origin, Length, Angle));
    }

    Struct = *laser_init(TX1);
}

void Laser::calcDist(std::vector<Block>& Blocks, Vector2D& Origin, double Angle) {
    Vector2D Res;
    bool Intersects;

    Struct.val_left = 2200;
    Struct.front_value = 2200;
    Struct.val_right = 2200;

    update(Origin, Angle);

    for (auto &B : Blocks) {
        // Laser cannot sense windows
        if (B.Type == BlockType::Window)
            continue;

        Intersects = B.intersection(Rays[0], Res);
        if (Intersects) Struct.val_left = std::min(Struct.val_left, (uint16_t)Res.length());

        Intersects = B.intersection(Rays[1], Res);
        if (Intersects) Struct.front_value = std::min(Struct.front_value, (uint16_t)Res.length());

        Intersects = B.intersection(Rays[2], Res);
        if (Intersects) Struct.val_right = std::min(Struct.val_right, (uint16_t)Res.length());
    }

    if (Struct.val_left > Length) Struct.val_left = 2200;
    if (Struct.front_value > Length) Struct.front_value = 2200;
    if (Struct.val_right > Length) Struct.val_right = 2200;
}

void Laser::update(Vector2D Origin, double Angle) {
    Rays[0].update(Origin, Angle + (M_PI / 2));
    Rays[1].update(Origin, Angle);
    Rays[2].update(Origin, Angle - (M_PI / 2));
}

void Laser::draw() {
    for (auto &Ray : Rays) {
        Ray.draw();
    }
}