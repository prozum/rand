#pragma once

#include <vector>

#include "Renderer.h"

class Simulator;

class SimObject {
    static Simulator *DefaultSim;
public:
    Simulator *Sim;

    Dot Pos;

    SimObject(Dot Pos);
    static void setDefaultSimulator(Simulator *Sim);

    virtual void draw() = 0;
    virtual void update() = 0;
};

