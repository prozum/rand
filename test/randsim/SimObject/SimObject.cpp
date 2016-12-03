#include "SimObject.h"

Simulator *SimObject::DefaultSim;

SimObject::SimObject(Dot Pos) : Pos(Pos) {
    Sim = DefaultSim;
}

void SimObject::setDefaultSimulator(Simulator *Sim) {
    DefaultSim = Sim;
}
