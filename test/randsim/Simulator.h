#pragma once

#include <memory>
#include <vector>

//The room is 300 cm high
#define ROOM_HEIGHT 300

class Renderer;
class Block;
class Drone;
class Minimap;

class Simulator {

public:
    std::unique_ptr<Renderer> Render;

    std::unique_ptr<Drone> Drn;
    std::unique_ptr<Minimap> Map;
    std::vector<Block> Blocks;

    unsigned int DeltaTime_Millis;

    Simulator();
    ~Simulator();

    int run();

    void drawObjects();
    void updateObjects();
    bool loadMap(std::string Path);

    void drawBlockGrid();
    void drawInfoBox();

private:
    unsigned int frameStartTime;
};
