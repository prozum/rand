#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"

class SdlRenderer : public Renderer {
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    TTF_Font *Font;

    int Fps = 60;
    int MinFrameTime = 1000 / Fps;
    int FrameTime = 0;

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
    void drawText(std::string Text, Dot Pos);

    // Relative
    void drawLineRel(Dot Start, Dot End);
    void drawRectRel(Dot Pos, int Width, int Height);
    void drawCircleRel(Dot Center, int Radius);
    void drawTextRel(std::string Text, Dot Pos);
};

