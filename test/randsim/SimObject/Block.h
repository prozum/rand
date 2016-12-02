#pragma once

#include "SimObject.h"

enum class BlockType {
    Air,
    Wall,
    Window
};

class Block : SimObject {

    BlockType Type;
    Dot Pos;

public:
    static const int Size = 50;

    Block(BlockType Type, Dot Pos);

    void draw();

    void update();
};

