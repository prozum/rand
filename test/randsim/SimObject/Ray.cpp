#include "Ray.h"

Ray::Ray(Vector2D Origin, double Length, double Angle) : length(Length), angle(Angle), Origin(Origin) {
    update(Angle);
}

void Ray::update(double Angle) {
    Direction.compose(this->length, Angle);
}

void Ray::update(Vector2D Origin, double Angle) {
    Direction.compose(this->length, Angle);
    this->Origin = Origin;
}
