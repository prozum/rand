#pragma once

#include <memory>
#include <vector>

#include "Renderer.h"

class Block;
class Drone;

class Simulator {

public:
    std::unique_ptr<Renderer> Render;

    std::unique_ptr<Drone> Drn;
    std::vector<Block> Blocks;

    Simulator();
    ~Simulator();

    int run();

    void drawObjects();
    void updateObjects();
    bool loadMap(std::string Path);

    void drawBlockGrid();
};
