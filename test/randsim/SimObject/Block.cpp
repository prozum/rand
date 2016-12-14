#include "Block.h"
#include "Simulator.h"

using namespace std;

Block::Block(Vector2D Pos, BlockType Type) : SimObject(Pos), Type(Type) {
    Min.X = Pos.X - (Size / 2);
    Min.Y = Pos.Y - (Size / 2);

    Max.X = Pos.X + (Size / 2);
    Max.Y = Pos.Y + (Size / 2);
}

void Block::draw() {
    switch (Type) {
        case BlockType::Air:
            Sim->Render->setColor(WHITE);
            break;
        case BlockType::Wall:
            Sim->Render->setColor(BLACK);
            break;
        case BlockType::Window:
            Sim->Render->setColor(BLUE);
            break;
    }
    Sim->Render->drawRectRel({Min.X, Max.Y}, {Size, Size});
}

void Block::update() {

}

bool Block::intersect(Ray Ray, Vector2D &Res) {
    double tx1 = (Min.X - Ray.Origin.X) / Ray.Direction.X;
    double tx2 = (Max.X - Ray.Origin.X) / Ray.Direction.X;

    double tmin = min(tx1, tx2);
    double tmax = max(tx1, tx2);

    double ty1 = (Min.Y - Ray.Origin.Y) / Ray.Direction.Y;
    double ty2 = (Max.Y - Ray.Origin.Y) / Ray.Direction.Y;

    tmin = max(tmin, min(ty1, ty2));
    tmax = min(tmax, max(ty1, ty2));

    Res = Ray.Direction * tmin;

    return tmax > max(tmin, 0.0);
}
