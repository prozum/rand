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
    static constexpr double Size = 25;

    Vector2D Min;
    Vector2D Max;

    Block(Vector2D Pos, BlockType Type);

    void draw();
    void update();
    bool intersection(Ray Ray, Vector2D& res);
};

