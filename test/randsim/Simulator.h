#pragma once

#include "SdlRenderer.h"
#include "Map.h"

class Simulator {

public:
    std::unique_ptr<Renderer> Render;
    std::unique_ptr<Map> M;

    Simulator();
    ~Simulator();

    int run();

    void drawObjects();
};
