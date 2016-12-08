#include "Block.h"
#include "Drone.h"
#include "Simulator.h"
#include "Minimap.h"
#include "SdlRenderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>

using namespace std;

Simulator::Simulator() {
    SimObject::setDefaultSimulator(this);
    Render = make_unique<SdlRenderer>();
    Drn = make_unique<Drone>(Vector2D(500, -500), 50);
    Map = make_unique<Minimap>();

    frameStartTime = 0;
}

Simulator::~Simulator() {
}

int Simulator::run() {
    SDL_Event Event;

    if (!Render->init()) {
        return 1;
    }

    if (!loadMap(string(SDL_GetBasePath()) + "map.txt")) {
        return 1;
    }

    if (!Map->loadMap(string(SDL_GetBasePath()) + "minimap.txt")) {
        return 1;
    }

    while (true) {
        DeltaTime_Millis = frameStartTime - SDL_GetTicks();
        frameStartTime = SDL_GetTicks();
        //printf("Delta-time: %d\n", DeltaTime_Millis);

        while (SDL_PollEvent(&Event) == 1) {
            switch (Event.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    switch(Event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            Render->Offset.X += int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_LEFT:
                            Render->Offset.X -= int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_UP:
                            Render->Offset.Y += int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_DOWN:
                            Render->Offset.Y -= int(1 / Render->Zoom) ?
                                                int(1 / Render->Zoom) * Block::Size : Block::Size;
                            break;
                        case SDLK_ESCAPE:
                            return 0;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        Render->WinWidth = Event.window.data1;
                        Render->WinHeight = Event.window.data2;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    Render->Zoom += Event.wheel.y * 0.2;
                    if (Render->Zoom < 0.2)
                        Render->Zoom = 0.2;
                    if (Render->Zoom > 10)
                        Render->Zoom = 10;
                    break;
            }
        }

        Render->clear();

        drawObjects();
        updateObjects();

        Render->update();
    }
}

void Simulator::drawObjects() {
    drawBlockGrid();

    for (auto B : Blocks) {
        B.draw();
    }

    Drn->draw();

    drawInfoBox();
    Map->draw();
}

void Simulator::updateObjects() {
    Drn->update();
}

bool Simulator::loadMap(string Path) {
    ifstream File;

    // Open file
    File.open(Path);
    if (!File.is_open()) {
        cout << "Couldn't open file: " << Path << endl;
        return false;
    }

    double X = Block::Size / 2;
    double Y = Block::Size / 2;
    char C;
    while ((C = File.get()) != EOF) {
        switch (C) {
            case CHAR_WALL:
                Blocks.push_back(Block({X, Y}, BlockType::Wall));
                X += Block::Size;
                break;
            case CHAR_TRANSPARENT:
                Blocks.push_back(Block({X, Y}, BlockType::Window));
                X += Block::Size;
                break;
            case CHAR_UNVISITED:
                X += Block::Size;
                break;
            case '\n':
                Y -= Block::Size;
                X = Block::Size / 2;
                break;
            default:
                cout << "Wrong character in file: '" << C << "'" << endl;
                return false;
        }
    }

    return true;
}

void Simulator::drawBlockGrid() {
    int WinHeight = Render->WinHeight;
    int WinWidth = Render->WinWidth;

    int RelBlockSize = int(Block::Size * Render->Zoom);

    int HLines = WinHeight / RelBlockSize;
    int VLines = WinWidth / RelBlockSize;

    Render->setColor({0, 0, 0});

    for (int i = 1; i <= HLines; ++i) {
        int CorY = i * RelBlockSize;
        int RealY = int(-Render->Offset.Y + Block::Size * i);
        if (RealY % 100 != 0) {
            Render->drawLine({0, CorY}, {WinWidth, CorY});
        } else if (RealY != 0) {
            Render->drawLine({0, CorY - 1}, {WinWidth, CorY - 1});
            Render->drawLine({0, CorY}, {WinWidth, CorY});
            Render->drawLine({0, CorY + 1}, {WinWidth, CorY + 1});
        } else {
            Render->setColor({255, 0, 0});
            Render->drawLine({0, CorY - 1}, {WinWidth, CorY - 1});
            Render->drawLine({0, CorY}, {WinWidth, CorY});
            Render->drawLine({0, CorY + 1}, {WinWidth, CorY + 1});
            Render->setColor({0, 0, 0});
        }
    }

    for (int i = 1; i <= VLines; ++i) {
        int CorX = i * RelBlockSize;
        int RealX = int(Render->Offset.X + Block::Size * i);
        if (RealX % 100 != 0) {
            Render->drawLine({CorX, 0}, {CorX, WinHeight});
        } else if (RealX != 0) {
            Render->drawLine({CorX - 1, 0}, {CorX - 1, WinHeight});
            Render->drawLine({CorX, 0}, {CorX, WinHeight});
            Render->drawLine({CorX + 1, 0}, {CorX + 1, WinHeight});
        } else {
            Render->setColor({255, 0, 0});
            Render->drawLine({CorX - 1, 0}, {CorX - 1, WinHeight});
            Render->drawLine({CorX, 0}, {CorX, WinHeight});
            Render->drawLine({CorX + 1, 0}, {CorX + 1, WinHeight});
            Render->setColor({0, 0, 0});
        }
    }
}

void Simulator::drawInfoBox() {
    int Height = Render->WinHeight * 0.7;
    int Width = Render->WinHeight * 0.3;

    Vector2D Pos = {int(Render->WinWidth - Width), int(Render->WinHeight - Height)};
    int MarginX = 25, MarginY = 25;
    int OffsetX = Pos.X + MarginX, OffsetY = Pos.Y + MarginY;

    // Design constants
    const int Indent = OffsetX + 10;
    const int ObjSpace = 40;
    const int PropSpace = 20;

    // Draw backgound
    Color BGColor = {35, 35, 35};
    Render->setColor(BGColor);
    Render->drawRect(Pos, Vector2D(Width, Height));

    // Text color
    Render->setColor({255, 255, 255}, 100);

    // Mouse info
    int MouseOffset = OffsetY;
    Render->drawText(string("Mouse: "), {OffsetX, MouseOffset}, BGColor);

    // Mouse pos
    int MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);
    Render->drawText(string("Pos : (") + DoubleToStr(Render->iRelX(MouseX)) + " cm, " + DoubleToStr(Render->iRelY(MouseY)) + " cm)", {Indent, MouseOffset + PropSpace}, BGColor);

    // Drone info
    int DroneOffset = MouseOffset + PropSpace + ObjSpace;
    Render->drawText(string("Drone:"), {OffsetX, DroneOffset}, BGColor);
    Render->drawText(string("Pos: (") + DoubleToStr(Drn->Pos.X) + " cm, " + DoubleToStr(Drn->Pos.Y) + " cm)", {Indent, DroneOffset + PropSpace}, BGColor);
    Render->drawText(string("Angle: ") + DoubleToStr(RadToDeg(Drn->Angle) + ','), {Indent, DroneOffset + PropSpace * 2}, BGColor);
    Render->drawText(string("Height: ") + DoubleToStr(Drn->Height) + " cm", {Indent, DroneOffset + PropSpace * 3}, BGColor);

    // Laser info
    int LaserOffset = DroneOffset + PropSpace * 3 + ObjSpace;
    Render->drawText(string("Laser:"), {OffsetX, LaserOffset}, BGColor);
    Render->drawText(string("Front: ") + DoubleToStr(Drn->Laser.front_value) + " cm", {Indent, LaserOffset + PropSpace * 1}, BGColor);
    Render->drawText(string("Left: ")  + DoubleToStr(Drn->Laser.left_value ) + " cm", {Indent, LaserOffset + PropSpace * 2}, BGColor);
    Render->drawText(string("Right: ") + DoubleToStr(Drn->Laser.right_value) + " cm", {Indent, LaserOffset + PropSpace * 3}, BGColor);

    // Sonar info
    int SonarOffset = LaserOffset + PropSpace * 3 + ObjSpace;
    Render->drawText(string("Sonar:"), {OffsetX, SonarOffset}, BGColor);
    Render->drawText(string("Front: ") + DoubleToStr(Drn->SonarModule.SonarStruct.value) + " cm", {Indent, SonarOffset + PropSpace * 1}, BGColor);

    //IR info
    int IROffset = SonarOffset + PropSpace + ObjSpace;
    Render->drawText(string("IR:"), {OffsetX, IROffset}, BGColor);
    Render->drawText(string("Bottom: ") + DoubleToStr(Drn->IrBottom.value), {Indent, IROffset + PropSpace * 1}, BGColor);
    Render->drawText(string("Top: ") + DoubleToStr(Drn->IrTop.value), {Indent, IROffset + PropSpace * 2}, BGColor);

    // Block to cm meter
    int MeterHeight = Block::Size * 4;
    int MeterTopY = Render->WinHeight - MeterHeight - MarginY;
    int MeterBotY =  Render->WinHeight - MarginY;
    Render->drawLine({OffsetX + 10, MeterTopY}, {OffsetX + 30, MeterTopY});
    Render->drawLine({OffsetX + 19, MeterTopY}, {OffsetX + 19, MeterBotY});
    Render->drawLine({OffsetX + 20, MeterTopY}, {OffsetX + 20, MeterBotY});
    Render->drawLine({OffsetX + 21, MeterTopY}, {OffsetX + 21, MeterBotY});
    Render->drawLine({OffsetX + 10, MeterBotY}, {OffsetX + 30, MeterBotY});
    Render->drawText(DoubleToStr(Render->iRel(MeterHeight)) + string("cm"), {OffsetX + 30, MeterTopY + MeterHeight / 2 - 15}, BGColor);
}

