#include "Ray.h"

Ray::Ray(Vector2D Origin, double Length, double Angle) : Length(Length), Angle(Angle), Origin(Origin) {
    update(Angle);
}

void Ray::update(double Angle) {
    Direction.compose(Length, Angle);
}

void Ray::update(Vector2D Origin, double Angle) {
    Direction.compose(Length, Angle);
    this->Origin = Origin;
}
