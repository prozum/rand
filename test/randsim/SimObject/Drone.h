#pragma once

#include <fc/fc.h>
#include "Renderer.h"
#include "SimObject.h"
#include "Sonar.h"
#include "Vector2D.h"

class Drone : public SimObject {
public:
    double Angle;   // Angle in radians
    int Size;       // Size in cm

    Sonar Sonar;
    fc_t FC;
    laser_t Laser;
    ir_t IrTop;
    ir_t IrBottom;

    Drone(Vector2D Pos, int Size);

    void draw();
    void update();
    void calcSonarDist();
    void calcLaserDist();
};
