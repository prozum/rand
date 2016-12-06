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
    Font = TTF_OpenFont(path.c_str(), 26);
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


void SdlRenderer::drawLine(Vector2D Start, Vector2D End) {
    SDL_RenderDrawLine(Renderer, Start.X, Start.Y, End.X, End.Y);
}

void SdlRenderer::drawLineRel(Vector2D Start, Vector2D End) {
    SDL_RenderDrawLine(Renderer, relX(Start.X), relY(Start.Y), relX(End.X), relY(End.Y));
}

void SdlRenderer::drawRect(Vector2D Pos, int Width, int Height) {
    const SDL_Rect Rect = {int(Pos.X), int(Pos.Y), Width, Height};
    SDL_RenderFillRect(Renderer, &Rect);
}

void SdlRenderer::drawRectRel(Vector2D Pos, int Width, int Height) {
    const SDL_Rect Rect = {relX(Pos.X), relY(Pos.Y), rel(Width), rel(Height)};
    SDL_RenderFillRect(Renderer, &Rect);
}

void SdlRenderer::drawCircle(Vector2D Center, int Radius) {
    filledCircleRGBA(Renderer, (Uint16)Center.X, (Uint16)Center.Y, (Uint16)Radius, CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}
void SdlRenderer::drawCircleRel(Vector2D Center, int Radius) {
    filledCircleRGBA(Renderer, (Uint16)relX(Center.X), (Uint16)relY(Center.Y), (Uint16)rel(Radius), CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}

void SdlRenderer::drawText(std::string Text, Vector2D Pos, Color BG) {
    auto TextSurface = TTF_RenderText_Shaded(Font, Text.c_str(), CurColor, {(Uint8)BG.R, (Uint8)BG.B, (Uint8)BG.G, 0});
    auto TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    SDL_Rect Quad = {int(Pos.X), int(Pos.Y), TextSurface->w, TextSurface->h};

    SDL_RenderCopyEx(Renderer, TextTexture, NULL, &Quad, 0, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(TextTexture);

}
void SdlRenderer::drawTextRel(std::string Text, Vector2D Pos, Color Background) {}

void SdlRenderer::drawPie(Vector2D Center, int Radius, int Start, int End) {
    filledPieRGBA(Renderer, int(Center.X), int(Center.Y), Radius, Start, End, CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}

void SdlRenderer::drawPieRel(Vector2D Center, int Radius, int Start, int End) {
    filledPieRGBA(Renderer, relX(Center.X), relY(Center.Y), rel(Radius), Start, End, CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}

void SdlRenderer::initMinimap(int Width, int Height) {
    MinimapWidth = Width;
    MinimapHeight = Height;

    auto Texture = SDL_CreateTexture(Renderer, 0, 0, MinimapWidth, MinimapWidth);
    SDL_SetRenderTarget(Renderer, Texture);
}

void SdlRenderer::drawMinimapPixel(int X, int Y, Color Color) {

}
