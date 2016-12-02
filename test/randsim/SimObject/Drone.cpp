#include "Simulator.h"
#include "Drone.h"

#include <cmath>

Drone::Drone(Dot Pos, int Size) : SimObject(Pos), Size(Size) { Angle = 0; }

void Drone::draw() {
    Sim->Render->drawCircleRel(Pos, Size / 2);

    Sim->Render->setColor({255, 0, 0});
    Sim->Render->drawLineRel(Pos, {Pos.X + int(sin(Angle) * Size / 2), Pos.Y + int(cos(Angle) * Size / 2)});
}

void Drone::update() {
    Angle = (Angle + 0.1);
    if (Angle > M_PI * 2)
        Angle = 0;
}

