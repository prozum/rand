#pragma once

#include <string>

struct Dot {
    int X;
    int Y;
};

struct Color {
    int R;
    int G;
    int B;
};

class Renderer {
public:
    virtual bool init() = 0;

    virtual void clear() = 0;
    virtual void update() = 0;

    virtual void setColor(Color C) = 0;

    virtual void drawLine(Dot Start, Dot End) = 0;
    virtual void drawRect(Dot Pos, int Width, int Height) = 0;
    virtual void drawCircle(Dot Center, int Radius) = 0;
    virtual void drawText(std::string Text, Dot Pos) = 0;
};

