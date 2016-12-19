#include "BlockBuilder.h"
#include <algorithm>
#include <iostream>

BlockBuilder::BlockBuilder(Simulator &Sim) : Sim(Sim) {}

void BlockBuilder::handleEvent(SDL_Event &Event) {
    switch (Event.type) {
    case SDL_MOUSEBUTTONDOWN: {
        Pressed = true;
        First = true;
        break;
    }
    case SDL_MOUSEBUTTONUP: {
        Pressed = false;
        DeleteMode = false;
        break;
    }
    }

    if (Pressed) {
        int MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);
        createBlock(MouseX, MouseY);
    }
}

void BlockBuilder::createBlock(int X, int Y) {
    auto relX = Sim.Render->iRelX(X);
    auto relY = Sim.Render->iRelY(Y);

    // Match blocks
    bool Match = Sim.Blocks.end() !=
                 std::find_if(Sim.Blocks.begin(), Sim.Blocks.end(),
                              [relX, relY](Block &B) -> bool {
                                  return relX >= B.Min.X && relX < B.Max.X &&
                                         relY >= B.Min.Y && relY < B.Max.Y;
                              });

    // Check if delete mode
    if (First) {
        DeleteMode = Match;
        First = false;
    }

    // Delete block
    if (DeleteMode) {
        auto Iter = std::remove_if(Sim.Blocks.begin(), Sim.Blocks.end(),
                                   [relX, relY](Block &B) -> bool {
                                       return relX >= B.Min.X &&
                                              relX < B.Max.X &&
                                              relY >= B.Min.Y && relY < B.Max.Y;
                                   });
        Sim.Blocks.erase(Iter, Sim.Blocks.end());
    }

    // Create new block
    if (!Match && !DeleteMode) {
        auto newX = int(relX / Block::Size) * Block::Size;
        auto newY = int(relY / Block::Size) * Block::Size;
        newX += relX >= 0 ? Block::Size / 2 : -Block::Size / 2;
        newY += relY >= 0 ? Block::Size / 2 : -Block::Size / 2;
        Sim.Blocks.push_back(Block({newX, newY}, CurType));
    }
}

void BlockBuilder::setCurBlockType(BlockType Type) { CurType = Type; }
