#pragma once

#include "SimObject.h"
#include "Ray.h"

enum class BlockType {
    Air,
    Wall,
    Window
};

class Block : public SimObject {
    BlockType Type;

public:
    static const int Size = 25;

    Vector2D min;
    Vector2D max;

    Block(Dot Pos, BlockType Type);

    void draw();
    void update();
    bool intersection(Ray ray);
};

