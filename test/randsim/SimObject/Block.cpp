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

    //printf("%f, %lf\n", res.X, res.Y);

    res = Ray.Direction * tmin;

    return tmax > std::max(tmin, 0.0);


    /*
    double tmin = (Min.X - Ray.Origin.X) * Ray.Inverted.X;
    double tmax = (Max.X - Ray.Origin.X) * Ray.Inverted.X;

    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (Min.Y - Ray.Origin.Y) * Ray.Inverted.Y;
    double tymax = (Max.Y - Ray.Origin.Y) * Ray.Inverted.Y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin) tmin = tymin;

    if (tymax < tmax) tmax = tymax;

    res.X = Ray.Direction.X * tmin;
    res.Y = Ray.Direction.Y * tymin;


    return true;
     */
}
