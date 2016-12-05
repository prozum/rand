#include "Simulator.h"
#include "Drone.h"

extern "C" {
#include "nav/nav.h"
}

#include <cmath>

inline double rad_to_deg(double radians) {
    return radians * (180.0 / M_PI);
}

Drone::Drone(Dot Pos, int Size) : SimObject(Pos), Size(Size), Angle(0) { }

void Drone::draw() {
    // Drone
    Sim->Render->drawCircleRel(Pos, Size / 2);

    // Direction line
    Sim->Render->setColor({255, 0, 0});
    Sim->Render->drawLineRel(Pos, {Pos.X + int(cos(Angle) * Size / 2), Pos.Y + int(sin(Angle) * Size / 2)});

    // Sonar
    Sim->Render->setColor({255, 0, 0}, 100);
    Sim->Render->drawPieRel(Pos, 500, int(rad_to_deg(Angle) - 7.5), int(rad_to_deg(Angle) + 7.5));

    // Laser
    Sim->Render->setColor({0, 0, 255}, 100);
    Sim->Render->drawPieRel(Pos, 400, int(rad_to_deg(Angle) - 135), int(rad_to_deg(Angle) + 135));
}

void Drone::update() {
    navigation(&FC, &Laser, &Sonar, &IrTop, &IrBottom);

    //Angle = float(Angle + 0.05);
    if (Angle > M_PI * 2)
        Angle = 0;
}

