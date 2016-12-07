#include "SimObject.h"

Simulator *SimObject::DefaultSim;

SimObject::SimObject(Vector2D Pos) {
    Sim = DefaultSim;
    this->Pos = Pos;
}

void SimObject::setDefaultSimulator(Simulator *Sim) {
    DefaultSim = Sim;
}
