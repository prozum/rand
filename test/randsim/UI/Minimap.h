#pragma once

#include <vector>
#include <memory>
#include <string>

#include "UI/Renderer.h"
#include "SimObject.h"
#include "Block.h"

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
