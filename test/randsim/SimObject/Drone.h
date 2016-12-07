#pragma once

extern "C" {
#include "fc/fc.h"
#include "nav/nav.h"
}
#include "Renderer.h"
#include "SimObject.h"
#include "Sonar.h"
#include "Vector2D.h"

class Drone : public SimObject {
public:
    double Angle;   // Angle in radians
    double Size;       // Size in cm

    Sonar SonarModule;
    fc_t FC;
    laser_t Laser;
    ir_t IrTop;
    ir_t IrBottom;

    rep_t WorldRepresentation;
    nav_t NavigationStruct;

    Drone(Vector2D Pos, int Size);

    void draw();
    void update();
    void calcLaserDist();
};
