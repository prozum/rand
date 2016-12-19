#pragma once

#include <vector>

#include "Common/Vector2D.h"
#include "UI/Renderer.h"

class Simulator;

class SimObject {
    static Simulator *DefaultSim;

  public:
    Simulator *Sim;

    Vector2D Pos;

    SimObject();
    SimObject(Vector2D Pos);
    static void setDefaultSimulator(Simulator *Sim);

    virtual void draw() = 0;
    virtual void update() = 0;
};
