#pragma once

#include "Renderer.h"

class Simulator;

class SimObject {
    static Simulator *DefaultSim;
public:
    Simulator *Sim;

    SimObject();
    static void setDefaultSimulator(Simulator *Sim);

    virtual void draw() = 0;
    virtual void update() = 0;
};

