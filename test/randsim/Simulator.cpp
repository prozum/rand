#include "Simulator.h"
#include "Map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

Simulator::Simulator() {
    SimObject::setDefaultSimulator(this);
    Render = make_unique<SdlRenderer>();
    M = make_unique<Map>();

    M.loadMap(string(SDL_GetBasePath()) + "map.txt");
}

Simulator::~Simulator() {
}

int Simulator::run() {
    SDL_Event event;

    Render->init();

    M->printMap();

    while (true) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        Render->clear();

        drawObjects();

        Render->update();
    }
}

void Simulator::drawObjects() {
    M->draw();
}

