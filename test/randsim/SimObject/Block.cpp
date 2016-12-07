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

bool Block::intersection(Ray Ray, Vector2D &res) {
    double tx1 = (Min.X - Ray.Origin.X) * Ray.Inverted.X;
    double tx2 = (Max.X - Ray.Origin.X) * Ray.Inverted.X;

    double tmin = std::min(tx1, tx2);
    double tmax = std::max(tx1, tx2);

    double ty1 = (Min.Y - Ray.Origin.Y) * Ray.Inverted.Y;
    double ty2 = (Max.Y - Ray.Origin.Y) * Ray.Inverted.Y;

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    res = Ray.Direction * tmin;

    return tmax >= tmin;
}
