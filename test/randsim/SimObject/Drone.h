#pragma once

extern "C" {
#include "fc/fc.h"
#include "nav/nav.h"
#include "ir/ir.h"
}
#include "Renderer.h"
#include "SimObject.h"
#include "Sonar.h"
#include "Vector2D.h"
#include "Simulator.h"

#define ROTATION_SPEED 0.05
#define STRAFE_SPEED 1 //defines speed in the left, right direction
#define MOVEMENT_SPEED 1 //defines speed in forward, backward directoin
#define ALTITUDE_SPEED 1 //defines speed in up/down direction

#define FC_OFFSET 1
#define ROTATION_OFFSET -NINETY_DEGREES_IN_RAD

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

private:
    void updateRotation(uint16_t yaw_value);
    void updateStrafe(uint16_t roll_value);
    void updateFrontal(uint16_t pitch_value);
    void updateHeight(uint16_t throttle_value);
    void updateFromFC();

    float height;
    uint16_t counter;
};
