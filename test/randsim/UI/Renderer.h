#pragma once

#include <cmath>
#include <sstream>
#include <string>

#include "Common/Vector2D.h"

struct Color {
    int R; //!< Red
    int G; //!< Green
    int B; //!< Blue
};

#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

#define WHITE                                                                  \
    { 255, 255, 255 }
#define YELLOW                                                                 \
    { 255, 255, 0 }
#define RED                                                                    \
    { 255, 0, 0 }
#define GREEN                                                                  \
    { 0, 255, 0 }
#define BLUE                                                                   \
    { 0, 0, 255 }
#define BLACK                                                                  \
    { 0, 0, 0 }

inline double RadToDeg(double Radians) { return Radians * (180.0 / M_PI); }

inline double DegToRad(double Degrees) { return (Degrees / 180.0) * M_PI; }

#define NINETY_DEGREES_IN_RAD M_PI_2
#define MINIMAP_BLOCK_SIZE 10

// String functions
std::string DoubleToStr(double Double, int Precision = 5);

class Renderer {
  public:
    int WinWidth = 1000;
    int WinHeight = 1000;
    float Zoom = 1.0;
    Vector2D Offset = {-500, 500};

    int Fps;

    virtual bool init() = 0;

    virtual void clear() = 0;
    virtual void update() = 0;

    virtual void setColor(Color C, int Alpha = 255) = 0;

    // Fixed
    virtual void drawLine(Vector2D Start, Vector2D End) = 0;
    virtual void drawRect(Vector2D Pos, Vector2D Size) = 0;
    virtual void drawCircle(Vector2D Center, int Radius) = 0;
    virtual void drawPie(Vector2D Center, int Radius, int Start, int End) = 0;
    virtual void drawText(std::string Text, Vector2D Pos,
                          Color Background = {0, 0, 0}) = 0;
    virtual void drawPixel(Vector2D Pos) = 0;

    // Relative
    virtual void drawLineRel(Vector2D Start, Vector2D End) = 0;
    virtual void drawRectRel(Vector2D Pos, Vector2D Size) = 0;
    virtual void drawCircleRel(Vector2D Center, int Radius) = 0;
    virtual void drawPieRel(Vector2D Center, int Radius, int Start,
                            int End) = 0;
    virtual void drawTextRel(std::string Text, Vector2D Pos,
                             Color Background = {0, 0, 0}) = 0;

    // Targets
    virtual void setScreenTarget() = 0;
    virtual void setMinimapTarget() = 0;
    virtual void drawTarget(Vector2D Pos, Vector2D Size,
                            bool Screen = false) = 0;

    // Relative functions
    inline int rel(double Val) { return int(Val * Zoom); }
    inline int relX(double Val) { return int((Val - Offset.X) * Zoom); }
    inline int relY(double Val) { return int(-(Val - Offset.Y) * Zoom); }

    // Inverse relative functions
    inline double iRel(double Val) { return Val / Zoom; }
    inline double iRelX(double Val) { return Val / Zoom + Offset.X; }
    inline double iRelY(double Val) { return -(Val / Zoom - Offset.Y); }
};
