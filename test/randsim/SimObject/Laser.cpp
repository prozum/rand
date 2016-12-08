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
    double TmpDist;
    bool Intersects;

    update(Origin, Angle);

    for (auto &B : Blocks) {
        Intersects = B.intersection(Rays[0], Res);
        if (Intersects) {
            TmpDist = Res.length();
            Struct.left_value = std::min(Struct.left_value, (uint16_t)TmpDist);
        }

        Intersects = B.intersection(Rays[1], Res);
        if (Intersects) {
            TmpDist = Res.length();
            Struct.front_value = std::min(Struct.front_value, (uint16_t)TmpDist);
        }

        Intersects = B.intersection(Rays[2], Res);
        if (Intersects) {
            TmpDist = Res.length();
            Struct.right_value = std::min(Struct.right_value, (uint16_t)TmpDist);
        }
    }

    if (Struct.left_value > Length) Struct.left_value = LASER_MAX_DISTANCE_M * 100;
    if (Struct.front_value > Length) Struct.front_value = LASER_MAX_DISTANCE_M * 100;
    if (Struct.right_value > Length) Struct.right_value = LASER_MAX_DISTANCE_M * 100;
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