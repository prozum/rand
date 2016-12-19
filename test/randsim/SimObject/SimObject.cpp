#include "SimObject.h"

Simulator *SimObject::DefaultSim;

SimObject::SimObject() : SimObject(Vector2D(0, 0)) {}
SimObject::SimObject(Vector2D Pos) {
    Sim = DefaultSim;
    this->Pos = Pos;
}

void SimObject::setDefaultSimulator(Simulator *Sim) { DefaultSim = Sim; }
