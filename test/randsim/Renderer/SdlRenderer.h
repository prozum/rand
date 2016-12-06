#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

#include "Renderer.h"

class SdlRenderer : public Renderer {
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    TTF_Font *Font;
    SDL_Color CurColor = {0, 0, 0, 0};

    int Fps = 60;
    int MinFrameTime = 1000 / Fps;
    int FrameTime = 0;

    int MinimapWidth;
    int MinimapHeight;

public:
    bool init();
    ~SdlRenderer();

    void clear();
    void update();

    void setColor(Color C, int Alpha = 255);

    // Fixed
    void drawLine(Dot Start, Dot End);
    void drawRect(Dot Pos, int Width, int Height);
    void drawCircle(Dot Center, int Radius);
    void drawPie(Dot Center, int Radius, int Start, int End);
    void drawText(std::string Text, Dot Pos, Color BG = {0, 0, 0});

    // Relative
    void drawLineRel(Dot Start, Dot End);
    void drawRectRel(Dot Pos, int Width, int Height);
    void drawCircleRel(Dot Center, int Radius);
    void drawPieRel(Dot Center, int Radius, int Start, int End);
    void drawTextRel(std::string Text, Dot Pos, Color Background = {0, 0, 0});

    // Minimap
    void initMinimap(int Width, int Height);
    void drawMinimapPixel(int X, int Y, Color Color);
};

