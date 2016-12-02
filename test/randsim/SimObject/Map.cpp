#include "Map.h"

#include "../Simulator.h"

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

Map::Map() {}

void Map::loadMap(string Path) {
    ifstream File(Path, ifstream::in);
    auto lastRow = make_unique<vector<BlockType>>();

    char c;
    while ((c = File.get()) != EOF) {
        switch (c) {
            case AIR_CHAR:
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
}

void Map::printMap() {
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
}

void Map::draw() {
    int X = 0;
    int Y = 0;
    for(auto &Row : MapBlocks) {
        for (auto &Block : *Row) {
            switch (Block) {
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
            Sim->Render->drawRect({X,Y}, 20, 20);
            X+=21;
        }
        Y+=21;
        X=0;
    }
}

void Map::update() {

}
