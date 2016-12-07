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
    Sim->Render->drawRectRel({Min.X, Min.Y}, {Size, Size});
}

void Block::update() {

}

bool Block::intersection(Ray ray, Vector2D& res) {

    double tminx, tmaxx, tminy, tmaxy;

    if (ray.Direction.X == 0) {
        if (Min.X > ray.Origin.X && Max.X < ray.Origin.X) {
            auto t1 = fabs(Min.Y - ray.Origin.Y);
            auto t2 = fabs(Max.Y - ray.Origin.Y);
            res.X = ray.Origin.X;
            res.Y = ray.Origin.Y - std::min(t1, t2);

        }
    } else if (ray.Direction.Y == 0) {
        if (Min.Y > ray.Origin.Y && Max.Y < ray.Origin.Y) {
            auto t1 = fabs(Min.X - ray.Origin.X);
            auto t2 = fabs(Max.X - ray.Origin.X);
            res.X = ray.Origin.X - std::min(t1, t2);
            res.Y = ray.Origin.Y;
        }
    }

    tminx = (Min.X - ray.Origin.X) / ray.Direction.X;
    tminy = (Min.Y - ray.Origin.Y) / ray.Direction.Y;

    tmaxx = (Max.X - ray.Origin.X) / ray.Direction.X;
    tmaxy = (Max.Y - ray.Origin.Y) / ray.Direction.Y;

    if ((tminx > tmaxy) || (tminy > tmaxy)) return false;

    if (tminy > tminx) tminx = tminy;
    if (tmaxy < tmaxx) tmaxx = tmaxy;

    res = ray.Direction * (tminx < 0 ? tmaxx : tminx);

    return true;
}

