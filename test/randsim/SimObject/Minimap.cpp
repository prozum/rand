#include "Minimap.h"
#include "Simulator.h"

extern "C" {
#include "map/map.h"
}

#include <iostream>
#include <fstream>
#include <memory>
#include <SDL_system.h>

using namespace std;

#define MAP_HEIGHT 64
#define MAP_WIDTH  64

Minimap::Minimap() : SimObject(Vector2D()) {
    map_init(MAP_WIDTH, MAP_HEIGHT, 0);
}

bool Minimap::loadMap(string Path) {
    ifstream File;

    // Open file
    File.open(Path);
    if (!File.is_open()) {
        cout << "Couldn't open file: " << Path << endl;
        return false;
    }

    char C;
    int X = 0, Y = 0;
    while ((C = File.get()) != EOF) {
        switch (C) {
            case CHAR_UNVISITED:
                map_write(X++, Y, UNVISITED);
                break;
            case CHAR_VISITED:
                map_write(X++, Y, VISITED);
                break;
            case CHAR_WALL:
                map_write(X++, Y, WALL);
                break;
            case CHAR_TRANSPARENT:
                map_write(X++, Y, WINDOW);
                break;
            case '\n':
                Y++;
                X = 0;
                break;
            default:
                cout << "Wrong character in file: '" << C << "'" << endl;
                return false;
        }
    }
    return true;
}

void Minimap::printMap() {
    map_show();
}

void Minimap::draw() {
    auto WinWidth  = Sim->Render->WinWidth;
    auto WinHeight = Sim->Render->WinHeight;
    auto MapWidth  = WinHeight * 0.3;
    auto MapHeight = WinHeight * 0.3;
    auto BlockSize = Vector2D(ceil(MapWidth / MAP_WIDTH), ceil(MapHeight / MAP_HEIGHT));
    //Sim->Render->setColor({0, 255, 255});
    //Sim->Render->drawRect(Vector2D(WinWidth - WinHeight * 0.3, 0.0), Vector2D(WinHeight * 0.3, WinHeight * 0.3));
    //map_show();

    Sim->Render->setColor(WHITE);
    Sim->Render->drawRect({WinWidth - MapWidth, 0.0}, {MapWidth, MapHeight});

    Sim->Render->setColor(BLACK);
    Sim->Render->drawLine({WinWidth - MapWidth, 0.0}, {WinWidth - MapWidth, MapHeight});
    Sim->Render->drawLine({WinWidth - MapWidth, MapHeight}, {double(WinWidth), MapHeight});

    for(int X = 0; X < MAP_WIDTH; ++X) {
        for(int Y = 0; Y < MAP_HEIGHT; ++Y) {
            fieldstate_t Val = map_read(X, Y);
            auto realX = (WinWidth - MapWidth) + X * BlockSize.X;
            auto realY = Y * BlockSize.Y;
            switch (Val) {
                case UNVISITED:
                    //Sim->Render->setColor({255, 0, 0});
                    //Sim->Render->drawRect({realX, realY}, BlockSize);
                    //Sim->Render->drawPixel({realX, realY});
                    break;
                case VISITED:
                    Sim->Render->setColor(YELLOW);
                    Sim->Render->drawRect({realX, realY}, BlockSize);
                    break;
                case WALL:
                    Sim->Render->setColor(BLACK);
                    Sim->Render->drawRect({realX, realY}, BlockSize);
                    break;
                case WINDOW:
                    Sim->Render->setColor(BLUE);
                    Sim->Render->drawRect({realX, realY}, BlockSize);
                    break;
                default:
                    exit(1);
                    break;
            }
        }
    }
}

void Minimap::update() {

}
