#include "SdlRenderer.h"

#include "iostream"

extern "C" {
#include "map/map.h"
}

using namespace std;

bool SdlRenderer::init() {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << " Failed to initialize SDL : " << SDL_GetError() << endl;
        return false;
    }

    // Init Window
    Window = SDL_CreateWindow("randsim", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WinWidth, WinHeight,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
    // SDL_RenderSetLogicalSize(Renderer, WindowRect.w, WindowRect.h);

    // Init SDL TrueType Font
    if (TTF_Init() == -1) {
        std::cout << " Failed to initialize TTF : " << SDL_GetError()
                  << std::endl;
        return false;
    }

    // Load font
    std::string path =
        std::string(SDL_GetBasePath()) + string("Fonts/Ubuntu-C.ttf");
    Font = TTF_OpenFont(path.c_str(), 18);
    if (Font == nullptr) {
        std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
        return false;
    }

    MinimapTexture = SDL_CreateTexture(
        Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        MAP_WIDTH * MINIMAP_BLOCK_SIZE, MAP_HEIGHT * MINIMAP_BLOCK_SIZE);
    if (MinimapTexture == nullptr) {
        std::cout << " Failed to create texture : " << SDL_GetError()
                  << std::endl;
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
    setColor(WHITE);
    SDL_RenderClear(Renderer);
}

void SdlRenderer::update() {
    SDL_RenderPresent(Renderer);

    auto FrameTime = SDL_GetTicks() - LastTime;
    if (FrameTime < MinFrameTime)
        SDL_Delay(MinFrameTime - FrameTime);

    Fps = 1000 / (SDL_GetTicks() - LastTime);

    LastTime = SDL_GetTicks();
}

void SdlRenderer::setColor(Color C, int Alpha) {
    CurColor = {(Uint8)C.R, (Uint8)C.G, (Uint8)C.B, (Uint8)Alpha};
    SDL_SetRenderDrawColor(Renderer, CurColor.r, CurColor.g, CurColor.b,
                           CurColor.a);
}

void SdlRenderer::drawLine(Vector2D Start, Vector2D End) {
    SDL_RenderDrawLine(Renderer, Start.X, Start.Y, End.X, End.Y);
}

void SdlRenderer::drawLineRel(Vector2D Start, Vector2D End) {
    SDL_RenderDrawLine(Renderer, relX(Start.X), relY(Start.Y), relX(End.X),
                       relY(End.Y));
}

void SdlRenderer::drawRect(Vector2D Pos, Vector2D Size) {
    const SDL_Rect Rect = {int(Pos.X), int(Pos.Y), int(Size.X), int(Size.Y)};
    SDL_RenderFillRect(Renderer, &Rect);
}

void SdlRenderer::drawRectRel(Vector2D Pos, Vector2D Size) {
    const SDL_Rect Rect = {relX(Pos.X), relY(Pos.Y), rel(Size.X), rel(Size.Y)};
    SDL_RenderFillRect(Renderer, &Rect);
}

void SdlRenderer::drawCircle(Vector2D Center, int Radius) {
    filledCircleRGBA(Renderer, (Uint16)Center.X, (Uint16)Center.Y,
                     (Uint16)Radius, CurColor.r, CurColor.g, CurColor.b,
                     CurColor.a);
}
void SdlRenderer::drawCircleRel(Vector2D Center, int Radius) {
    filledCircleRGBA(Renderer, (Uint16)relX(Center.X), (Uint16)relY(Center.Y),
                     (Uint16)rel(Radius), CurColor.r, CurColor.g, CurColor.b,
                     CurColor.a);
}

void SdlRenderer::drawText(std::string Text, Vector2D Pos, Color BG) {
    auto TextSurface =
        TTF_RenderText_Shaded(Font, Text.c_str(), CurColor,
                              {(Uint8)BG.R, (Uint8)BG.B, (Uint8)BG.G, 0});
    auto TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    SDL_Rect Quad = {int(Pos.X), int(Pos.Y), TextSurface->w, TextSurface->h};

    SDL_RenderCopyEx(Renderer, TextTexture, NULL, &Quad, 0, NULL,
                     SDL_FLIP_NONE);
    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(TextTexture);
}
void SdlRenderer::drawTextRel(std::string Text, Vector2D Pos,
                              Color Background) {}

void SdlRenderer::drawPie(Vector2D Center, int Radius, int Start, int End) {
    filledPieRGBA(Renderer, int(Center.X), int(Center.Y), Radius, Start, End,
                  CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}

void SdlRenderer::drawPieRel(Vector2D Center, int Radius, int Start, int End) {
    filledPieRGBA(Renderer, relX(Center.X), relY(Center.Y), rel(Radius), Start,
                  End, CurColor.r, CurColor.g, CurColor.b, CurColor.a);
}

void SdlRenderer::drawPixel(Vector2D Pos) {
    SDL_RenderDrawPoint(Renderer, Pos.X, Pos.Y);
}

void SdlRenderer::setScreenTarget() {
    SDL_SetRenderTarget(Renderer, NULL);
    CurTexture = nullptr;
}

void SdlRenderer::setMinimapTarget() {
    SDL_SetRenderTarget(Renderer, MinimapTexture);
    CurTexture = MinimapTexture;
}

void SdlRenderer::drawTarget(Vector2D Pos, Vector2D Size, bool ToScreen) {
    if (CurTexture == nullptr) {
        std::cout << "Don't draw screen texture to other texture" << std::endl;
        return;
    }

    if (ToScreen)
        SDL_SetRenderTarget(Renderer, NULL);

    SDL_Rect RenderQuad = {int(Pos.X), int(Pos.Y), int(Size.X), int(Size.Y)};
    SDL_RenderCopyEx(Renderer, CurTexture, NULL, &RenderQuad, 0, 0,
                     SDL_FLIP_NONE);

    if (ToScreen)
        SDL_SetRenderTarget(Renderer, CurTexture);
}
