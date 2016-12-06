#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Renderer.h"
#include "SimObject.h"
#include "Block.h"

extern "C" {
#include "map/map.h"
}

#define AIR_CHAR ' '
#define WALL_CHAR '#'
#define WINDOW_CHAR '&'

#define YELLOW {255, 255, 0}
#define BLUE   {0, 0, 255}
#define BLACK  {0, 0, 0}

class Minimap : SimObject {

public:
    unsigned long Width = 0;
    unsigned long Height = 0;

    Minimap();

    void loadMap(std::string Path);
    void printMap();
    void draw();
    void update();
};
