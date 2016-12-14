#pragma once

extern "C" {
#include "fc/fc.h"
#include "nav/nav.h"
#include "ir/ir.h"
}
#include "UI/Renderer.h"
#include "SimObject.h"
#include "Sonar.h"
#include "Common/Vector2D.h"
#include "Simulator.h"
#include "Laser.h"

// All speeds are measured in cm (or rads)/sec
#define ROTATION_SPEED M_PI/2
#define STRAFE_SPEED   20.0 // Defines speed in the left, right direction
#define MOVEMENT_SPEED 100.0 // Defines speed in forward, backward direction
#define ALTITUDE_SPEED 10.0 // Defines speed in up/down direction

#define FC_OFFSET 1
#define ROTATION_OFFSET M_PI
#define NAV_UPDATE_TIME 100

class Drone : public SimObject {
public:
    double Angle;    // Angle in radians
    double Size;     // Size in cm
    double Height;

    Sonar SonarModule;
    Laser LaserModule;
    fc_t FC;
    ir_t IrTop;
    ir_t IrBottom;

    rep_t WorldRepresentation;
    nav_t NavStruct;

    Drone(Vector2D Pos, int Size);

    void draw();
    void update();

private:
    void updateYaw(uint16_t YawValue);
    void updateRoll(uint16_t RollValue);
    void updatePitch(uint16_t PitchValue);
    void updateThrottle(uint16_t ThrottleValue);
    void updateFromFC();

    double calcAcceleration(double PrevVel, double NewVel);
    double calcVelocity(double DirectionValue, const double Speed);
    double calcDistance(const double Speed, double DeltaTime);

    unsigned int LastNavUpdate;
};
