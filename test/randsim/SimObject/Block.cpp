#include "Block.h"
#include "Simulator.h"

Block::Block(BlockType Type, Dot Pos) {
    this->Type = Type;
    this->Pos = Pos;
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
    Sim->Render->drawRectRel({Pos.X, Pos.Y}, Size, Size);
}

void Block::update() {

}


