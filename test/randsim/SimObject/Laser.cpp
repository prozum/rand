#include "Laser.h"

Laser::Laser(Vector2D Origin, double Length, double Angle)
        : Pos(Origin), Length(Length), Angle(Angle) {

    for (int i = 0; i < 3; ++i) {
        Rays.push_back(Ray(Origin, Length, Angle));
    }

    LaserStruct = *laser_init(TX1);
}

void Laser::calcDist(std::vector<Block>& Blocks, Vector2D& Origin, double Angle) {
    Vector2D Res;
    double TmpDist;
    bool Intersects;

    update(Origin, Angle);

    for (auto &B : Blocks) {
        Intersects = B.intersection(Rays[0], Res);
        TmpDist = Res.length();
        if (Intersects && TmpDist <= Length) {
            Struct.left_value = Res.length();
        } else {
            Struct.left_value = 2200;
        }

        Intersects = B.intersection(Rays[1], Res);
        TmpDist = Res.length();
        if (Intersects && TmpDist <= Length) {
            Struct.front_value = Res.length();
        }
        else {
            Struct.front_value = 2200;
        }

        Intersects = B.intersection(Rays[2], Res);
        TmpDist = Res.length();
        if (Intersects && TmpDist <= Length) {
            Struct.right_value = Res.length();
        }
        else {
            Struct.right_value = 2200;
        }
    }
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