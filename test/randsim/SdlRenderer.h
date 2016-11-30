#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"

class SdlRenderer : public Renderer {
    SDL_Rect WindowRect = {900, 300, 1050, 1050};
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

    void setColor(Color C);

    void drawLine(Dot Start, Dot End);
    void drawRect(Dot Pos, int Width, int Height);
    void drawCircle(Dot Center, int Radius);
    void drawText(std::string Text, Dot Pos);
};

