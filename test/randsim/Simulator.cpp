#include "Simulator.h"
#include "Map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

Simulator::Simulator() {
    M.loadMap("map.txt");
}

Simulator::~Simulator() {
}

int Simulator::run() {
    SDL_Event event;

    M.printMap();

    Renderer.init();

    while (true) {
        Renderer.start();
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        Renderer.clear();

        M.draw(Renderer);

        Renderer.update();
    }
}

