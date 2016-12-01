#include "SdlRenderer.h"

#include "iostream"

using namespace std;

bool SdlRenderer::init() {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << " Failed to initialize SDL : " << SDL_GetError() << endl;
        return false;
    }

    // Init Window
    Window = SDL_CreateWindow("randsim", WindowRect.x, WindowRect.y, WindowRect.w, WindowRect.h, 0);
    if (Window == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }

    // Init SDL Renderer
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == nullptr) {
        cout << "Failed to create sdl renderer : " << SDL_GetError();
        return false;
    }
    //SDL_RenderSetLogicalSize(Renderer, WindowRect.w, WindowRect.h);

    // Init SDL TrueType Font
    if (TTF_Init() == -1)
    {
        std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
        return false;
    }

    // Load font
    std::string path = std::string(SDL_GetBasePath()) + string("fonts/Ubuntu-C.ttf");
    Font = TTF_OpenFont(path.c_str(), 90);
    if (Font == nullptr)
    {
        std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
        return false;
    }

}

SdlRenderer::~SdlRenderer() {
    TTF_CloseFont(Font);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void SdlRenderer::start() {
    FrameTime = SDL_GetTicks();
}

void SdlRenderer::clear() {
    SDL_RenderClear(Renderer);
}

void SdlRenderer::update() {
    SDL_RenderPresent(Renderer);

    if ((SDL_GetTicks() - FrameTime) < MinFrameTime)
        SDL_Delay(MinFrameTime - (SDL_GetTicks() - FrameTime));
}


void SdlRenderer::setColor(Color C) {
    SDL_SetRenderDrawColor(Renderer, (Uint8)C.R, (Uint8)C.G, (Uint8)C.B, 255);
}


void SdlRenderer::drawLine(Dot Start, Dot End) {
    SDL_RenderDrawLine(Renderer, Start.X, Start.Y, End.X, End.Y);
}
void SdlRenderer::drawRect(Dot Pos, int Width, int Height) {
    const SDL_Rect Rect = {Pos.X, Pos.Y, Width, Height};
    //SDL_RenderDrawRect(Renderer, &Rect);
    SDL_RenderFillRect(Renderer, &Rect);
}
void SdlRenderer::drawCircle(Dot Center, int Radius) {}
void SdlRenderer::drawText(std::string Text, Dot Pos) {}