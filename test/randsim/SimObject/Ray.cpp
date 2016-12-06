#include "Ray.h"

Ray::Ray(Vector2D Origin, double Length, double Angle) : Origin(Origin), length(Length), angle(Angle) {
    update(Angle);
}

void Ray::update(double Angle) {
    Direction.compose(this->length, Angle);
}

void Ray::update(Vector2D Origin, double Angle) {
    Direction.compose(this->length, Angle);
    this->Origin = Origin;
}