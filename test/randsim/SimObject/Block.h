#pragma once

#include "SimObject.h"

enum class BlockType {
    Air,
    Wall,
    Window
};

class Block : SimObject {
    BlockType Type;

public:
    static const int Size = 50;

    Block(Dot Pos, BlockType Type);

    void draw();
    void update();
};

