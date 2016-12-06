#include "Map.h"

#include "../Simulator.h"

extern "C" {
#include "map/map.h"
}

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

#define MAP_HEIGHT 64
#define MAP_WIDTH  64

Map::Map() : SimObject(Dot()) {
    map_init(MAP_WIDTH, MAP_HEIGHT, 0);
}

void Map::loadMap(string Path) {
    /*
    ifstream File(Path, ifstream::in);
    auto lastRow = make_unique<vector<BlockType>>();

    char c;
    int x = 0, y = 0;
    while ((c = File.get()) != EOF) {
        switch (c) {
            case AIR_CHAR:
                map_write(x, y, BlockType::Air);
                lastRow->push_back(BlockType::Air);
                break;
            case WALL_CHAR:
                lastRow->push_back(BlockType::Wall);
                break;
            case WINDOW_CHAR:
                lastRow->push_back(BlockType::Window);
                break;
            case '\n':
                MapBlocks.push_back(move(lastRow));
                lastRow = make_unique<vector<BlockType>>();
                break;
            default:
                cout << "Wrong character in file:" << c;
                return;
        }
    }
    MapBlocks.push_back(move(lastRow));

    Width = MapBlocks.size();
    Height = MapBlocks[0]->size();
     */
}

void Map::printMap() {
    /*
    for(auto &Row : MapBlocks) {
        for (auto &Block : *Row) {
            switch (Block) {
                case BlockType::Air:
                    cout << AIR_CHAR;
                    break;
                case BlockType::Wall:
                    cout << WALL_CHAR;
                    break;
                case BlockType::Window:
                    cout << WINDOW_CHAR;
                    break;
            }
        }
        cout << endl;
    }
     */
}

void Map::draw() {
    int Val;
    for(int X = 0; X < MAP_WIDTH; ++X) {
        for(int Y = 0; Y < MAP_HEIGHT; ++Y) {
            Val = map_read(X, Y);
            switch (Val) {
                /*
                case BlockType::Air:
                    Sim->Render->setColor({255, 255, 255});
                    break;
                case BlockType::Wall:
                    Sim->Render->setColor({0, 0, 0});
                    break;
                case BlockType::Window:
                    Sim->Render->setColor({0, 0, 255});
                    break;
                    */
            }
            Sim->Render->drawRect({X,Y}, 20, 20);
        }
        X=0;
    }
}

void Map::update() {

}
