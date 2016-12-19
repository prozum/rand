#pragma once

#include "SDL.h"
#include "Simulator.h"
#include <SimObject/Block.h>

class BlockBuilder {
    Simulator &Sim;
    BlockType CurType = BlockType::Wall;
    bool Pressed = false;
    bool First = false;
    bool DeleteMode = false;

  public:
    BlockBuilder(Simulator &Sim);
    void handleEvent(SDL_Event &Event);
    void createBlock(int X, int Y);
    void setCurBlockType(BlockType Type);
};
