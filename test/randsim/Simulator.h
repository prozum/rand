#pragma once

#include "Map.h"
#include "SdlRenderer.h"

class Simulator {

public:
    SdlRenderer Renderer;

    Map M;

    Simulator();
    ~Simulator();
    int run();

};
