#pragma once

#include <memory>
#include <vector>

// The room is 300 cm high
#define ROOM_HEIGHT 300

class Renderer;
class Block;
class Drone;
class Minimap;
class BlockBuilder;

class Simulator {

  public:
    std::unique_ptr<Renderer> Render;
    std::unique_ptr<BlockBuilder> BBuilder;
    std::unique_ptr<Minimap> Map;

    std::unique_ptr<Drone> Drn;
    std::vector<Block> Blocks;

    unsigned int Time;
    unsigned int DeltaTime;

    Simulator();
    ~Simulator();

    int run();

    void drawObjects();
    void updateObjects();
    bool loadMap(std::string Path);

    void drawBlockGrid();
    void drawInfoBox();
};
