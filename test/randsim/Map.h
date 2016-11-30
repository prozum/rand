#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Renderer.h"
#include "SimObject.h"

#define AIR_CHAR ' '
#define WALL_CHAR '#'
#define WINDOW_CHAR '&'

enum class BlockType {
    Air,
    Wall,
    Window
};

class Map : SimObject {
    std::vector<std::unique_ptr<std::vector<BlockType>>> MapBlocks;

public:
    unsigned long Width = 0;
    unsigned long Height = 0;

    Map();

    void loadMap(std::string Path);
    void printMap();
    void draw();
    void update();
};
