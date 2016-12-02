#pragma once

#include "Renderer.h"
#include "SimObject.h"

class Drone : SimObject {
    Dot Pos;
    int Size;

public:
    Drone(Dot Pos, int Size);

    void draw();
    void update();
};
