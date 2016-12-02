#include <Simulator.h>
#include "Drone.h"

Drone::Drone(Dot Pos, int Size) : Pos(Pos), Size(Size) { }

void Drone::draw() {
    Sim->Render->drawCircleRel(Pos, Size / 2);
}

void Drone::update() { }

