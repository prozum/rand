#include "Laser.h"

Laser::Laser(Vector2D& Origin, double Length, double Angle)
        : Pos(Origin), Length(Length), Angle(Angle) {
    for (int i = 0; i < 3; ++i) {
        Rays.push_back(Ray(Origin, Angle, Length));
    }
}

void Laser::calcDist(std::vector<Block>& Blocks, Vector2D& Origin, double Angle) {

}

void Laser::update(Vector2D& Origin, double Angle) {

    double StartAngle = Angle - M_PI;

    for (int i = 0; i < 3; ++i) {
        Rays[i].update(Origin, StartAngle + (i * M_PI));
    }
}

void Laser::draw() {

}