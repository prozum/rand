#include "Block.h"
#include "Simulator.h"

Block::Block(Vector2D Pos, BlockType Type) : SimObject(Pos), Type(Type) {
    Min.X = Pos.X - (Size / 2);
    Min.Y = Pos.Y - (Size / 2);

    Max.X = Pos.X + (Size / 2);
    Max.Y = Pos.Y + (Size / 2);
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
    Sim->Render->drawRectRel({Min.X, Min.Y}, Size, Size);
}

void Block::update() {

}

bool Block::intersection(Ray ray, Vector2D& res) {
    Vector2D T1;
    Vector2D T2;

    if (ray.direction.X == 0) {
        if (ray.origin.X < Min.X || ray.origin.X > Max.X) {
            return false;
        }
    } else if (ray.direction.Y == 0) {
        if (ray.origin.Y < Min.Y || ray.origin.Y > Max.Y) {
            return false;
        }
    }

    T1.X = (Min.X - ray.origin.X) / ray.direction.X;
    T1.Y = (Min.Y - ray.origin.Y) / ray.direction.Y;

    T2.X = (Max.X - ray.origin.X) / ray.direction.X;
    T2.Y = (Max.Y - ray.origin.Y) / ray.direction.Y;

    if (T1.X > T2.X) {
        std::swap(T1.X, T2.X);
    }

    if (T1.Y > T2.Y) {
        std::swap(T1.X, T2.X);
    }

    if (T1.X > T1.Y || T2.Y > T1.X) {
        return false;
    }

    res.X = T1.X;
    res.Y = T2.X;

    return true;
}

