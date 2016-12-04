#include "Block.h"
#include "Drone.h"
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
    Drn = make_unique<Drone>(Dot(500, 500), 100);

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
                            Render->Offset.X += int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_LEFT:
                            Render->Offset.X -= int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_UP:
                            Render->Offset.Y -= int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_DOWN:
                            Render->Offset.Y += int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_ESCAPE:
                            return 0;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        Render->WinWidth = Event.window.data1;
                        Render->WinHeight = Event.window.data2;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    Render->Zoom += Event.wheel.y * 0.1;
                    if (Render->Zoom < 0.1)
                        Render->Zoom = 0.1;
                    break;
            }
        }

        Render->clear();

        drawObjects();
        updateObjects();

        Render->update();
    }
}

void Simulator::drawObjects() {
    drawBlockGrid();

    for (auto B : Blocks) {
        B.draw();
    }

    Drn->draw();

}

void Simulator::updateObjects() {
    Drn->update();
}

bool Simulator::loadMap(string Path) {
    ifstream File(Path, ifstream::in);

    int x = 0;
    int y = 0;
    char c;
    while ((c = File.get()) != EOF) {
        switch (c) {
            case WALL_CHAR:
                Blocks.push_back(Block({x, y}, BlockType::Wall));
                x += Block::Size;
                break;
            case WINDOW_CHAR:
                Blocks.push_back(Block({x, y}, BlockType::Window));
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

    Render->setColor({0, 0, 0});
    for (int i = 1; i <= HLines; ++i) {
        int LineY = i * BlockSize;
        Render->drawLine({0, LineY}, {Width, LineY});
    }

    for (int i = 1; i <= VLines; ++i) {
        int LineX = i * BlockSize;
        Render->drawLine({LineX, 0}, {LineX, Height});
    }
}

