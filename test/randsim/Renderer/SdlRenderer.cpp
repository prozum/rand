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
    Window = SDL_CreateWindow("randsim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WinWidth, WinHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (Window == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }

    // Init SDL Renderer
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == nullptr) {
        cout << "Failed to create sdl Renderer : " << SDL_GetError();
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
    std::string path = std::string(SDL_GetBasePath()) + string("Fonts/Ubuntu-C.ttf");
    Font = TTF_OpenFont(path.c_str(), 90);
    if (Font == nullptr)
    {
        std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

SdlRenderer::~SdlRenderer() {
    TTF_CloseFont(Font);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void SdlRenderer::clear() {
    setColor({255, 255, 255});
    SDL_RenderClear(Renderer);
}

void SdlRenderer::update() {
    SDL_RenderPresent(Renderer);

    if ((SDL_GetTicks() - FrameTime) < MinFrameTime)
        SDL_Delay(MinFrameTime - (SDL_GetTicks() - FrameTime));

    FrameTime = SDL_GetTicks();
}

void SdlRenderer::setColor(Color C, int Alpha) {
    CurColor = {(Uint8)C.R, (Uint8)C.G, (Uint8)C.B, (Uint8)Alpha };
    SDL_SetRenderDrawColor(Renderer, CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}


void SdlRenderer::drawLine(Dot Start, Dot End) {
    SDL_RenderDrawLine(Renderer, Start.X, Start.Y, End.X, End.Y);
}

void SdlRenderer::drawLineRel(Dot Start, Dot End) {
    SDL_RenderDrawLine(Renderer, rel(Start.X), rel(Start.Y), rel(End.X), rel(End.Y));
}

void SdlRenderer::drawRect(Dot Pos, int Width, int Height) {
    const SDL_Rect Rect = {Pos.X, Pos.Y, Width, Height};
    SDL_RenderFillRect(Renderer, &Rect);
}

void SdlRenderer::drawRectRel(Dot Pos, int Width, int Height) {
    const SDL_Rect Rect = {relX(Pos.X), relY(Pos.Y), rel(Width), rel(Height)};
    SDL_RenderFillRect(Renderer, &Rect);
}

void SdlRenderer::drawCircle(Dot Center, int Radius) {
    filledCircleRGBA(Renderer, (Uint16)Center.X, (Uint16)Center.Y, (Uint16)Radius, CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}
void SdlRenderer::drawCircleRel(Dot Center, int Radius) {
    filledCircleRGBA(Renderer, (Uint16)relX(Center.X), (Uint16)relY(Center.Y), (Uint16)rel(Radius), CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}

void SdlRenderer::drawText(std::string Text, Dot Pos) {}
void SdlRenderer::drawTextRel(std::string Text, Dot Pos) {}