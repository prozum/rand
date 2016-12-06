#include "Map.h"

#include "../Simulator.h"

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

Map::Map() : SimObject(Vector2D()) {
    map_init(MAP_WIDTH, MAP_HEIGHT, 0);
    Sim->Render->initMinimap(MAP_WIDTH, MAP_WIDTH);
}

void Map::loadMap(string Path) {
    ifstream File(Path, ifstream::in);

    char c;
    int x = 0, y = 0;

    while ((c = File.get()) != EOF) {
        switch (c) {
            case AIR_CHAR:
                map_write(x++, y, UNVISITED);
                break;
            case WALL_CHAR:
                map_write(x++, y, WALL);
                break;
            case WINDOW_CHAR:
                map_write(x++, y, TRANSPARENT);
                break;
            case '\n':
                y++;
                x = 0;
                break;
            default:
                cout << "Wrong character in file:" << c;
                return;
        }
    }
}

void Map::printMap() {
    map_show();
}

void Map::draw() {
    int Val;
    for(int X = 0; X < MAP_WIDTH; ++X) {
        for(int Y = 0; Y < MAP_HEIGHT; ++Y) {
            Val = map_read(X, Y);
            switch (Val) {
                case UNVISITED:
                    break;
                case VISITED:
                    Sim->Render->drawMinimapPixel(X, Y, YELLOW);
                    break;
                case WALL:
                    Sim->Render->drawMinimapPixel(X, Y, BLACK);
                    break;
                case TRANSPARENT:
                    Sim->Render->drawMinimapPixel(X, Y, BLUE);
                    break;
                default:
                    exit(1);
                    break;
            }
        }
    }
}

void Map::update() {

}
