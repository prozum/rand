#pragma once

#include <string>
#include <cmath>

#include "Vector2D.h"

struct Color {
    int R;
    int G;
    int B;
};

inline double RadToDeg(double Radians) {
    return Radians * (180.0 / M_PI);
}

// String functions
std::string DoubleToStr(double Double, int Precision = 5);

class Renderer {
public:
    int WinWidth = 1000;
    int WinHeight = 1000;
    float Zoom = 1.0;
    Vector2D Offset = {0, 0};

    virtual bool init() = 0;

    virtual void clear() = 0;
    virtual void update() = 0;

    virtual void setColor(Color C, int Alpha = 255) = 0;

    // Fixed
    virtual void drawLine(Vector2D Start, Vector2D End) = 0;
    virtual void drawRect(Vector2D Pos, int Width, int Height) = 0;
    virtual void drawCircle(Vector2D Center, int Radius) = 0;
    virtual void drawPie(Vector2D Center, int Radius, int Start, int End) = 0;
    virtual void drawText(std::string Text, Vector2D Pos, Color Background = {0, 0, 0}) = 0;

    // Relative
    virtual void drawLineRel(Vector2D Start, Vector2D End) = 0;
    virtual void drawRectRel(Vector2D Pos, int Width, int Height) = 0;
    virtual void drawCircleRel(Vector2D Center, int Radius) = 0;
    virtual void drawPieRel(Vector2D Center, int Radius, int Start, int End) = 0;
    virtual void drawTextRel(std::string Text, Vector2D Pos, Color Background = {0, 0, 0}) = 0;

    // Minimap
    virtual void initMinimap(int Width, int Height) = 0;
    virtual void drawMinimapPixel(int X, int Y, Color Color) = 0;

    // Relative functions
    inline int rel(double Val) { return int(Val * Zoom); }
    inline int relX(double Val) { return int((Val - Offset.X) * Zoom); }
    inline int relY(double Val) { return int((-Val - Offset.Y) * Zoom); }

    // Inverse relative functions
    inline double iRel(double Val) { return int(Val / Zoom); }
    inline double iRelX(double Val) { return int((Val / Zoom) + Offset.X); }
    inline double iRelY(int Val) { return int((-Val / Zoom) + Offset.Y); }

};

