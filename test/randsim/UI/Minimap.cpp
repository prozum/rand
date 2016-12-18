#include "Minimap.h"
#include "Simulator.h"
#include "Drone.h"

extern "C" {
#include "map/map.h"
}

#include <iostream>
#include <fstream>
#include <memory>
#include <SDL_system.h>
#include <SDL.h>

using namespace std;

Minimap::Minimap(Simulator &Sim) : Sim(Sim) {
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
    int X = 0, Y = MAP_HEIGHT - 1;
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
                Y--;
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
    auto WinWidth  = Sim.Render->WinWidth;
    auto WinHeight = Sim.Render->WinHeight;

    auto MinimapSize = Vector2D(WinHeight * 0.3, WinHeight * 0.3);
    auto MinimapPos = Vector2D(WinWidth - MinimapSize.X, 0.0);
    auto BlockSize = Vector2D(10, 10);


    Sim.Render->setMinimapTarget();
    Sim.Render->clear();

    for(int X = 0; X < MAP_WIDTH; ++X) {
        for(int Y = 0; Y < MAP_HEIGHT; ++Y) {
            fieldstate_t Val = map_read(X, (MAP_HEIGHT - 1) - Y);
            switch (Val) {
                case UNVISITED:
                    break;
                case VISITED:
                    Sim.Render->setColor(GREEN);
                    Sim.Render->drawRect({X * BlockSize.X, Y * BlockSize.Y}, BlockSize);
                    break;
                case WALL:
                    Sim.Render->setColor(BLACK);
                    Sim.Render->drawRect({X * BlockSize.X, Y * BlockSize.Y}, BlockSize);
                    break;
                case WINDOW:
                    Sim.Render->setColor(BLUE);
                    Sim.Render->drawRect({X * BlockSize.X, Y * BlockSize.Y}, BlockSize);
                    break;
            }
        }
    }

    // Current drone position
    auto CentPerBlock = CENTIMETERS_PR_PIXEL / double(MINIMAP_BLOCK_SIZE);
    auto MapHeightBlock = (MAP_HEIGHT - 1) * MINIMAP_BLOCK_SIZE;
    Sim.Render->setColor(RED);
    Sim.Render->drawRect({Sim.Drn->NavStruct.posx / CentPerBlock,
                           MapHeightBlock - Sim.Drn->NavStruct.posy / CentPerBlock}, BlockSize);


    Sim.Render->drawTarget(MinimapPos, MinimapSize, true);
    Sim.Render->setScreenTarget();
}

void Minimap::update() {

}
