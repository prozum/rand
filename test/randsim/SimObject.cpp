#include "SimObject.h"

Simulator *SimObject::DefaultSim;

SimObject::SimObject() {
    Sim = DefaultSim;
}

void SimObject::setDefaultSimulator(Simulator *Sim) {
    DefaultSim = Sim;
}
