#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SimObject/Block.h"
#include "SimObject/SimObject.h"
#include "UI/Renderer.h"

extern "C" {
#include "map/map.h"
}

class Minimap {
    Simulator &Sim;

  public:
    unsigned long Width = 0;
    unsigned long Height = 0;

    Minimap(Simulator &Sim);

    bool loadMap(std::string Path);
    void printMap();
    void draw();
    void update();
};
