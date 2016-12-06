#pragma once

#include <vector>

#include "Renderer.h"
#include "Vector2D.h"
#include "sonar/sonar.h"
#include "laser/laser.h"

class Simulator;

class SimObject {
    static Simulator *DefaultSim;
public:
    Simulator *Sim;

    Vector2D Pos;

    SimObject(Vector2D Pos);
    static void setDefaultSimulator(Simulator *Sim);

    double calcDist(SimObject *obj);
    double calcDist(double X, double Y);
    double calcAngle(double X, double Y);
    virtual void draw() = 0;
    virtual void update() = 0;
};

