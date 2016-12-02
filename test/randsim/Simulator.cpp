#include "Block.h"
#include "Simulator.h"
#include "Map.h"
#include "SdlRenderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>

using namespace std;

Simulator::Simulator() {
    SimObject::setDefaultSimulator(this);
    Render = make_unique<SdlRenderer>();

}

Simulator::~Simulator() {
}

int Simulator::run() {
    SDL_Event Event;

    if (!Render->init()) {
        return 1;
    }

    if (!loadMap(string(SDL_GetBasePath()) + "map.txt")) {
        return 1;
    }

    while (true) {
        while (SDL_PollEvent(&Event) == 1) {
            switch (Event.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    switch(Event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            Render->Offset.X += Block::Size;
                            break;
                        case SDLK_LEFT:
                            Render->Offset.X -= Block::Size;
                            break;
                        case SDLK_UP:
                            Render->Offset.Y -= Block::Size;
                            break;
                        case SDLK_DOWN:
                            Render->Offset.Y += Block::Size;
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        Render->WinWidth = Event.window.data1;
                        Render->WinHeight = Event.window.data2;
                    }
                    break;
            }
        }

        Render->clear();

        drawObjects();

        Render->update();
    }
}

void Simulator::drawObjects() {
    for (auto B : Blocks) {
        B.draw();
    }

    drawBlockGrid();
}

bool Simulator::loadMap(string Path) {
    ifstream File(Path, ifstream::in);

    int x = 0;
    int y = 0;
    char c;
    while ((c = File.get()) != EOF) {
        switch (c) {
            case WALL_CHAR:
                Blocks.push_back(Block(BlockType::Wall, {x, y}));
                x += Block::Size;
                break;
            case WINDOW_CHAR:
                Blocks.push_back(Block(BlockType::Window, {x, y}));
                x += Block::Size;
                break;
            case AIR_CHAR:
                x += Block::Size;
                break;
            case '\n':
                y += Block::Size;
                x = 0;
                break;
            default:
                cout << "Wrong character in file: '" << c << "'";
                return false;
        }
    }

    return true;
}

void Simulator::drawBlockGrid() {
    int Height = Render->WinHeight;
    int Width = Render->WinWidth;

    int BlockSize = int(Block::Size * Render->Zoom);

    int HLines = Height / BlockSize;
    int VLines = Width / BlockSize;

    for (int i = 1; i <= HLines; ++i) {
        int LineY = i * BlockSize;
        Render->drawLine({0, LineY}, {Width, LineY});
    }

    for (int i = 1; i <= VLines; ++i) {
        int LineX = i * BlockSize;
        Render->drawLine({LineX, 0}, {LineX, Height});
    }
}