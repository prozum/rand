#pragma once

#include "SimObject.h"
#include "Common/Ray.h"

enum class BlockType {
    Air,
    Wall,
    Window
};

class Block : public SimObject {

public:
    static constexpr double Size = 25;
    BlockType Type;

    Vector2D Min;
    Vector2D Max;

    Block(Vector2D Pos, BlockType Type);

    void draw();
    void update();
    bool intersect(Ray Ray, Vector2D &Res);
};

