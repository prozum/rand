#pragma once

#include <memory>
#include <vector>

#include "Renderer.h"

class Block;

class Simulator {

public:
    std::unique_ptr<Renderer> Render;
    std::vector<Block> Blocks;

    Simulator();
    ~Simulator();

    int run();

    void drawObjects();
    bool loadMap(std::string Path);

    void drawBlockGrid();
};
