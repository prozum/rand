#include "Block.h"
#include "Drone.h"
#include "Simulator.h"
#include "UI/Minimap.h"
#include "UI/SdlRenderer.h"
#include "UI/BlockBuilder.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>

using namespace std;

Simulator::Simulator()  {
    SimObject::setDefaultSimulator(this);

    Render = make_unique<SdlRenderer>();
    BBuilder = make_unique<BlockBuilder>(*this);
    Map = make_unique<Minimap>(*this);

    Drn = make_unique<Drone>(Vector2D(100.0, -100.0), 50);

    Time = 0;
    DeltaTime = 10;
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
        while (SDL_PollEvent(&Event) == 1) {
            BBuilder->handleEvent(Event);

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

        updateObjects();
        drawObjects();

        Render->update();
    }
}

void Simulator::drawObjects() {
    for (auto &B : Blocks) {
        B.draw();
    }
    drawBlockGrid();

    Drn->draw();

    drawInfoBox();
    Map->draw();
}

void Simulator::updateObjects() {
    Drn->update();
    Time += DeltaTime;
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
    double Y = - Block::Size / 2;
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
                cout << "Wrong character in file: '" << C << "'" << ", " << Path << endl;
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

    Render->setColor(BLACK);

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
            Render->setColor(RED);
            Render->drawLine({0, CorY - 1}, {WinWidth, CorY - 1});
            Render->drawLine({0, CorY}, {WinWidth, CorY});
            Render->drawLine({0, CorY + 1}, {WinWidth, CorY + 1});
            Render->setColor(BLACK);
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
            Render->setColor(RED);
            Render->drawLine({CorX - 1, 0}, {CorX - 1, WinHeight});
            Render->drawLine({CorX, 0}, {CorX, WinHeight});
            Render->drawLine({CorX + 1, 0}, {CorX + 1, WinHeight});
            Render->setColor(BLACK);
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

    // Simulation info
    int SimOffset = MouseOffset + PropSpace + ObjSpace;
    Render->drawText(string("Simulation:"), {OffsetX, SimOffset}, BGColor);
    Render->drawText(string("Drone Pos: (") + DoubleToStr(Drn->Pos.X) + " cm, " + DoubleToStr(Drn->Pos.Y) + " cm)", {Indent, SimOffset + PropSpace}, BGColor);
    Render->drawText(string("Drone Height: ") + DoubleToStr(Drn->Height) + " cm", {Indent, SimOffset + PropSpace * 2}, BGColor);
    Render->drawText(string("Drone Angle: ") + DoubleToStr(RadToDeg(Drn->Angle)) + " deg", {Indent, SimOffset + PropSpace * 3}, BGColor);

    // Drone info
    int DroneOffset = SimOffset + PropSpace * 3 + ObjSpace;
    Render->drawText(string("Drone:"), {OffsetX, DroneOffset}, BGColor);
    Render->drawText(string("Pos: (") + to_string(Drn->NavStruct.posx) + " cm, " + to_string(Drn->NavStruct.posy) + " cm)", {Indent, DroneOffset + PropSpace}, BGColor);
    Render->drawText(string("Angle: ") + to_string(Drn->NavStruct.angle * ANGLE_RESOLUTION) + " deg", {Indent, DroneOffset + PropSpace * 2}, BGColor);
    Render->drawText(string("Pitch: ") + DoubleToStr(fix16_to_float(Drn->FC.vel->y)) + " cm", {Indent, DroneOffset + PropSpace * 3}, BGColor);
    Render->drawText(string("Roll: ") + DoubleToStr(fix16_to_float(Drn->FC.vel->x)) + " cm", {Indent, DroneOffset + PropSpace * 4}, BGColor);
    Render->drawText(string("Throttle: ") + DoubleToStr(fix16_to_float(Drn->FC.vel->z)) + " cm", {Indent, DroneOffset + PropSpace * 5}, BGColor);
    Render->drawText(string("Yaw: ") + DoubleToStr(fix16_to_float(Drn->FC.gyro)) + " deg", {Indent, DroneOffset + PropSpace * 6}, BGColor);

    // Laser info
    int LaserOffset = DroneOffset + PropSpace * 6 + ObjSpace;
    Render->drawText(string("Laser:"), {OffsetX, LaserOffset}, BGColor);
    Render->drawText(string("Left: ")  + DoubleToStr(Drn->LaserModule.Struct.val_left ) + " cm", {Indent, LaserOffset + PropSpace * 1}, BGColor);
    Render->drawText(string("Front: ") + DoubleToStr(Drn->LaserModule.Struct.val_front) + " cm", {Indent, LaserOffset + PropSpace * 2}, BGColor);
    Render->drawText(string("Right: ") + DoubleToStr(Drn->LaserModule.Struct.val_right) + " cm", {Indent, LaserOffset + PropSpace * 3}, BGColor);

    // Sonar info
    int SonarOffset = LaserOffset + PropSpace * 3 + ObjSpace;
    Render->drawText(string("Sonar:"), {OffsetX, SonarOffset}, BGColor);
    Render->drawText(string("Front: ") + DoubleToStr(Drn->SonarModule.Struct.value) + " cm", {Indent, SonarOffset + PropSpace * 1}, BGColor);

    // IR info
    int IROffset = SonarOffset + PropSpace + ObjSpace;
    Render->drawText(string("IR:"), {OffsetX, IROffset}, BGColor);
    Render->drawText(string("Bottom: ") + DoubleToStr(Drn->IrBottom.value), {Indent, IROffset + PropSpace * 1}, BGColor);
    Render->drawText(string("Top: ") + DoubleToStr(Drn->IrTop.value), {Indent, IROffset + PropSpace * 2}, BGColor);

    // Block info
    int BlockOffset = IROffset + PropSpace * 2 + ObjSpace;
    Render->drawText(string("Block:"), {OffsetX, BlockOffset}, BGColor);
    Render->drawText(string("Count: ") + to_string(Blocks.size()), {Indent, BlockOffset + PropSpace * 1}, BGColor);

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

    // FPS
    Render->drawText(string("FPS: ")+ to_string(Render->Fps), {Render->WinWidth - 60, Render->WinHeight - 35}, BGColor);
}

