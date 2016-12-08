#include "Ray.h"

#include <stdio.h>
#include <Simulator.h>

Ray::Ray(Vector2D Origin, double Length, double Angle) : Length(Length), Angle(Angle), Origin(Origin) {
    update(Origin, Angle);
}

void Ray::update() {

}

void Ray::update(double Angle) {
    Direction.compose(Length, Angle);
}

void Ray::update(Vector2D Origin, double Angle) {
    Direction.compose(Length, Angle);
    this->Origin = Origin;
    this->Inverted = Origin.invert();
}

void Ray::draw() {
    Sim->Render->setColor(GREEN);
    Sim->Render->drawLineRel(Origin, Origin + Direction);
}
