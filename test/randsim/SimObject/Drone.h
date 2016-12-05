#pragma once

#include <fc/fc.h>
#include "Renderer.h"
#include "SimObject.h"

class Drone : public SimObject {
public:
    double Angle;
    int Size;

    fc_t FC;
    sonar_t Sonar;
    laser_t Laser;
    ir_t IrTop;
    ir_t IrBottom;

    Drone(Dot Pos, int Size);

    void draw();
    void update();

    void calcSonarDist();
    void calcLaserDist();
};
