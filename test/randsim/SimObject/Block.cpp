#include "Block.h"
#include "Simulator.h"

Block::Block(Vector2D Pos, BlockType Type) : SimObject(Pos), Type(Type) {
    min.x = Pos.x - (Size / 2);
    min.y = Pos.y - (Size / 2);

    max.x = Pos.x + (Size / 2);
    max.y = Pos.y + (Size / 2);
}

void Block::draw() {
    switch (Type) {
        case BlockType::Air:
            Sim->Render->setColor({255, 255, 255});
            break;
        case BlockType::Wall:
            Sim->Render->setColor({0, 0, 0});
            break;
        case BlockType::Window:
            Sim->Render->setColor({0, 0, 255});
            break;
    }
    Sim->Render->drawRectRel({Pos.x - Size / 2, Pos.x - Size / 2}, Size, Size);
}

void Block::update() {

}

bool Block::intersection(Ray ray, Vector2D& res) {
    Vector2D T1;
    Vector2D T2;

    if (ray.direction.x == 0) {
        if (ray.origin.x < min.x || ray.origin.x > max.x) {
            return false;
        }
    } else if (ray.direction.y == 0) {
        if (ray.origin.y < min.y || ray.origin.y > max.y) {
            return false;
        }
    }

    T1.x = (min.x - ray.origin.x) / ray.direction.x;
    T1.y = (min.y - ray.origin.y) / ray.direction.y;

    T2.x = (max.x - ray.origin.x) / ray.direction.x;
    T2.y = (max.y - ray.origin.y) / ray.direction.y;

    if (T1.x > T2.x) {
        std::swap(T1.x, T2.x);
    }

    if (T1.y > T2.y) {
        std::swap(T1.x, T2.x);
    }

    if (T1.x > T1.y || T2.y > T1.x) {
        return false;
    }

    res.x = T1.x;
    res.y = T2.x;

    return true;
}

