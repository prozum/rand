#pragma once

#include <string>

struct Dot {
    Dot(int X = 0, int Y = 0) {
        this->X = X;
        this->Y = Y;
    }
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
    int WinWidth = 1000;
    int WinHeight = 1000;
    float Zoom = 0.3;
    Dot Offset = {0, 0};

    virtual bool init() = 0;

    virtual void clear() = 0;
    virtual void update() = 0;

    virtual void setColor(Color C, int Alpha = 255) = 0;

    // Fixed
    virtual void drawLine(Dot Start, Dot End) = 0;
    virtual void drawRect(Dot Pos, int Width, int Height) = 0;
    virtual void drawCircle(Dot Center, int Radius) = 0;
    virtual void drawPie(Dot Center, int Radius, int Start, int End) = 0;
    virtual void drawText(std::string Text, Dot Pos) = 0;

    // Relative
    virtual void drawLineRel(Dot Start, Dot End) = 0;
    virtual void drawRectRel(Dot Pos, int Width, int Height) = 0;
    virtual void drawCircleRel(Dot Center, int Radius) = 0;
    virtual void drawPieRel(Dot Center, int Radius, int Start, int End) = 0;
    virtual void drawTextRel(std::string Text, Dot Pos) = 0;

    inline int rel(int Val) { return int(Val * Zoom); }
    inline int relX(int Val) { return int((Val - Offset.X) * Zoom); }
    inline int relY(int Val) { return int((Val - Offset.Y) * Zoom); }
};

