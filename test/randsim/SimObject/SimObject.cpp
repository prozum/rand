#include "SimObject.h"

Simulator *SimObject::DefaultSim;

SimObject::SimObject(Vector2D Pos) : Vector2D(Pos) {
    Sim = DefaultSim;
}

double SimObject::calcDist(SimObject *obj) {
    return sqrt(pow(obj->Pos.x - Pos.x, 2) + pow(obj->Pos.y - Pos.y, 2));
}

double SimObject::calcDist(double X, double Y) {
    return sqrt(pow(X - Pos.x, 2) + pow(Y - Pos.y, 2));
}

double SimObject::calcAngle(double X, double Y) {
    auto dx = X - Pos.x;
    auto dy = Y - Pos.x;

    if (dx == 0 && dy > 0) {
        return (270.0 * M_PI) /  180.0;
    } else if (dx == 0 && dy < 0) {
        return (90.0 * M_PI) /  180.0;
    } else if (dx > 0 && dy == 0) {
        return (0.0 * M_PI) /  180.0;
    } else if (dx < 0 && dy == 0) {
        return (180.0 * M_PI) /  180.0;
    } else {
        return atan2(dy, dx);
    }
}

void SimObject::setDefaultSimulator(Simulator *Sim) {
    DefaultSim = Sim;
}
